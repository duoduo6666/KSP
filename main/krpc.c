#include "esp_log.h"
#include "esp_err.h"

#include "krpc.pb-c.h"

static const char *TAG = "KSP-KRPC";


esp_err_t connect(){
    u_int8_t *buf;
    size_t len;
    
    Krpc__Schema__ConnectionRequest cr = KRPC__SCHEMA__CONNECTION_REQUEST__INIT;
    cr.type = KRPC__SCHEMA__CONNECTION_REQUEST__TYPE__RPC;
    cr.client_name = "ESP32";
    uint8_t zero_bytes[0];
    ProtobufCBinaryData zero = {
        .len = 0,
        .data = zero_bytes,
    };
    cr.client_identifier = zero;

    len = krpc__schema__connection_request__get_packed_size(&cr);
    buf = malloc(len);
    if (buf == NULL){
        ESP_LOGE(TAG, "内存分配失败");
        return ESP_FAIL;
    }
    krpc__schema__connection_request__pack(&cr,buf);

    for(int i=0; i<len; i++){
        ESP_LOGI(TAG, "%d: %x", i, buf[i]);
    }

    ESP_LOGI(TAG, "connect ok!");
    return ESP_OK;
}