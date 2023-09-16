#include "esp_log.h"
#include "esp_err.h"

#include "krpc.pb-c.h"
#include "varint.pb-c.h"

#include "socket.h"

#include "krpc.h"

#define MAX_RECV_LEN 8

#define KRPC_RECV_LEN(len) if (krpc_recv_len(&len) != ESP_OK){ESP_LOGE(TAG, "接收长度失败"); return ESP_FAIL;}
#define KRPC_RECV_DATA(buf, len) if (krpc_recv_data(buf, len) != ESP_OK){ESP_LOGE(TAG, "接收数据失败");}

#define MALLOC(ptr, size) ptr = malloc(size); if (ptr == NULL){ESP_LOGE(TAG, "内存分配失败"); return ESP_FAIL;}

static const char *TAG = "KSP-KRPC";

esp_err_t encode_varint(uint32_t value, uint8_t **varint_buf, size_t *varint_len){
    Varint varint = VARINT__INIT;
    varint.value = value;
    *varint_len = varint__get_packed_size(&varint);
    MALLOC(*varint_buf, *varint_len);
    varint__pack(&varint,*varint_buf);
    return ESP_OK;
}
uint32_t decode_varint(uint8_t *varint_buf, size_t varint_len){
    Varint *varint = varint__unpack(NULL, varint_len, varint_buf);
    uint32_t value = varint->value;
    varint__free_unpacked(varint, NULL);
    return value;
}
esp_err_t encode_double(double value, uint8_t **double_buf, size_t *double_len){
    Double double_ = DOUBLE__INIT;
    double_.value = value;
    *double_len = double__get_packed_size(&double_);
    MALLOC(*double_buf, *double_len);
    double__pack(&double_,*double_buf);
    return ESP_OK;
}
double decode_double(uint8_t *double_buf, size_t double_len){
    uint8_t buf[9];
    buf[0] = 0x09;
    for (uint8_t i=1; i<9; i++){
        buf[i] = double_buf[i-1];
    }
    Double *double_ = double__unpack(NULL, 9, buf);
    double value = double_->value;
    double__free_unpacked(double_, NULL);
    return value;
}

esp_err_t krpc_send(uint8_t *buf, size_t len){
    size_t varint_len;
    uint8_t *varint_buf;
    encode_varint(len, &varint_buf, &varint_len);

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
            ESP_LOGE(TAG, "recv len error: errno%d", errno);
            return ESP_FAIL;
        }

        // 接收长度大于1字节可能会引起异常
        varint = varint__unpack(NULL, i+1, buf);
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
    MALLOC(buf, len); 
    krpc__schema__connection_request__pack(&ConnectionRequest,buf);
    krpc_send(buf, len);
    free(buf);
    KRPC_RECV_LEN(len);
    MALLOC(buf, len); 
    KRPC_RECV_DATA(buf, len);
    Krpc__Schema__ConnectionResponse *ConnectionResponse = krpc__schema__connection_response__unpack(
        NULL, len, buf);
    free(buf);
    
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
    MALLOC(request.calls, sizeof(Krpc__Schema__ProcedureCall*) * request.n_calls);
    request.calls[0] = &call;

    len = krpc__schema__request__get_packed_size(&request);
    MALLOC(buf, len); 
    krpc__schema__request__pack(&request,buf);
    krpc_send(buf, len);
    free(request.calls);
    free(buf);
    
    KRPC_RECV_LEN(len);
    MALLOC(buf, len); 
    KRPC_RECV_DATA(buf, len);

    Krpc__Schema__Response *response = krpc__schema__response__unpack(NULL, len, buf);
    Krpc__Schema__Status *status = krpc__schema__status__unpack(
        NULL, response->results[0]->value.len, response->results[0]->value.data);
    ESP_LOGI(TAG, "kRPC server verison: %s", status->version);
    krpc__schema__response__free_unpacked(response, NULL);
    krpc__schema__status__free_unpacked(status, NULL);
    free(buf);
    return ESP_OK;
} 

esp_err_t krpc_Request(Krpc__Schema__Request *request, Krpc__Schema__Response **response){
    uint8_t *buf;
    size_t len;
    
    len = krpc__schema__request__get_packed_size(request);
    MALLOC(buf, len); 
    krpc__schema__request__pack(request,buf);
    krpc_send(buf, len);
    free(buf);
    
    KRPC_RECV_LEN(len);
    MALLOC(buf, len); 
    KRPC_RECV_DATA(buf, len);
    *response = krpc__schema__response__unpack(NULL, len, buf);
    free(buf);
    return ESP_OK;
}