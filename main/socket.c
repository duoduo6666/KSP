#include "esp_log.h"
#include "esp_err.h"

#include <sys/socket.h>

#define HOST_IP "192.168.1.128"
#define PORT 50000

static const char *TAG = "KSP-Socket";

// socket
int s;

struct sockaddr_in dest_addr;

esp_err_t socket_init(){
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s < 0){
        ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
        return ESP_FAIL;
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, HOST_IP, &dest_addr.sin_addr);
    
    int err = connect(s, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "Successfully connected");
    
    return ESP_OK;
}

esp_err_t socket_send_msg(uint8_t *msg, size_t len){
    int err = send(s, msg, len, 0);
    ESP_LOGI(TAG, "send err: %d ", err);
    if (err < 0){
        ESP_LOGE(TAG, "Socket 发送数据失败: errno %d", errno);
        return ESP_FAIL;
    }
    return ESP_OK;
}

esp_err_t socket_recv_byte(uint8_t *byte){
    uint8_t buf[1];
    int err = recv(s, buf, 1, MSG_WAITALL);
    if (err < 0){
        ESP_LOGE(TAG, "Socket 接收数据失败: errno %d", errno);
        return ESP_FAIL;
    }
    *byte = buf[0];
    return ESP_OK;
}

esp_err_t socket_recv_data(uint8_t *buf, size_t len){
    int err = recv(s, buf, len, MSG_WAITALL);
    ESP_LOGI(TAG, "recv data len: 0x%x", err);
    if (err < 0){
        ESP_LOGE(TAG, "Socket 接收数据失败: errno %d", errno);
        return ESP_FAIL;
    }
    return ESP_OK;
}