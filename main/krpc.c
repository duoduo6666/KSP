#include "esp_log.h"
#include "esp_err.h"

#include "krpc.pb-c.h"
#include "varint.pb-c.h"

#include "socket.h"

#define MAX_RECV_LEN 8

static const char *TAG = "KSP-KRPC";

esp_err_t krpc_send(u_int8_t *buf, size_t len){
    Varint varint = VARINT__INIT;
    varint.value = len;
    
    size_t varint_len = varint__get_packed_size(&varint);
    uint8_t *varint_buf = malloc(varint_len); 
    if (varint_buf == NULL){
        ESP_LOGE(TAG, "内存分配失败");
        return ESP_FAIL;
    }
    varint__pack(&varint,varint_buf);

    esp_err_t err0 = socket_send_msg(varint_buf+1, varint_len-1);
    esp_err_t err1 = socket_send_msg(buf, len);

    if (err0!=ESP_OK && err1!=ESP_OK){
        free(varint_buf);
        return ESP_OK;
    }else{
        free(varint_buf);
        return ESP_FAIL;
    }
}

esp_err_t krpc_recv_len(size_t *len){
    uint8_t buf[MAX_RECV_LEN+1];
    buf[0] = 0x08;
    Varint *varint = NULL;
    for (size_t i=1; i<MAX_RECV_LEN; i++){
    // for (size_t i=MAX_RECV_LEN-1; i>-1; i--){
        esp_err_t err = socket_recv_byte(buf+i);
        
        // recv error
        if (err != ESP_OK){
            if (varint != NULL){
                varint__free_unpacked(varint, NULL);
            }
            return ESP_FAIL;
        }

        varint = varint__unpack(NULL, i+1, buf);
        ESP_LOGI(TAG, "recv len: 0x%lx", varint->value);
        if (varint != NULL){
            *len = varint->value;
            varint__free_unpacked(varint, NULL);
            return ESP_OK;
        }
    }

    return ESP_FAIL;
}
esp_err_t krpc_recv_data(uint8_t *buf, size_t len){
    esp_err_t err = socket_recv_data(buf, len);
    return err;
}

esp_err_t krpc_connect(){
    uint8_t *buf;
    size_t len;
    
    Krpc__Schema__ConnectionRequest ConnectionRequest = KRPC__SCHEMA__CONNECTION_REQUEST__INIT;
    ConnectionRequest.type = KRPC__SCHEMA__CONNECTION_REQUEST__TYPE__RPC;
    ConnectionRequest.client_name = "ESP32";

    len = krpc__schema__connection_request__get_packed_size(&ConnectionRequest);
    buf = malloc(len); 
    if (buf == NULL){
        ESP_LOGE(TAG, "内存分配失败");
        return ESP_FAIL;
    }
    krpc__schema__connection_request__pack(&ConnectionRequest,buf);

    krpc_send(buf, len);
    free(buf);

    size_t recv_len;
    if (krpc_recv_len(&recv_len) != ESP_OK){
        ESP_LOGE(TAG, "接收长度失败");
        return ESP_FAIL;
    }
    uint8_t *recv_buf = malloc(recv_len);
    if (krpc_recv_data(recv_buf, recv_len) != ESP_OK){
        ESP_LOGE(TAG, "接收数据失败");
    }
    Krpc__Schema__ConnectionResponse *ConnectionResponse = krpc__schema__connection_response__unpack(
        NULL, recv_len, recv_buf);
    free(recv_buf);
    
    if (ConnectionResponse->status == 0){
        ESP_LOGI(TAG, "connect ok!");
        krpc__schema__connection_response__free_unpacked(ConnectionResponse, NULL);
        return ESP_OK;
    }else{
        ESP_LOGE(TAG, "connect error!");
        krpc__schema__connection_response__free_unpacked(ConnectionResponse, NULL);
        return ESP_OK;
    }
}

esp_err_t krpc_GetStatus(){
    uint8_t *buf;
    size_t len;

    Krpc__Schema__ProcedureCall call = KRPC__SCHEMA__PROCEDURE_CALL__INIT;
    call.service = "KRPC";
    call.procedure = "GetStatus";

    Krpc__Schema__Request request = KRPC__SCHEMA__REQUEST__INIT;
    request.n_calls = 1;
    request.calls = malloc(sizeof(Krpc__Schema__ProcedureCall*) * request.n_calls);
    request.calls[0] = &call;

    len = krpc__schema__request__get_packed_size(&request);
    buf = malloc(len); 
    if (buf == NULL){
        ESP_LOGE(TAG, "内存分配失败");
        return ESP_FAIL;
    }
    krpc__schema__request__pack(&request,buf);
    krpc_send(buf, len);
    free(request.calls);
    free(buf);
    
    size_t recv_len;
    if (krpc_recv_len(&recv_len) != ESP_OK){
        ESP_LOGE(TAG, "接收长度失败");
        return ESP_FAIL;
    }
    uint8_t *recv_buf = malloc(recv_len);
    if (krpc_recv_data(recv_buf, recv_len) != ESP_OK){
        ESP_LOGE(TAG, "接收数据失败");
    }

    Krpc__Schema__Response *response = krpc__schema__response__unpack( NULL, recv_len, recv_buf);
    Krpc__Schema__Status *status = krpc__schema__status__unpack(
        NULL, response->results[0]->value.len, response->results[0]->value.data);
    ESP_LOGI(TAG, "kRPC server verison: %s", status->version);
    free(recv_buf);
    return ESP_OK;
} 