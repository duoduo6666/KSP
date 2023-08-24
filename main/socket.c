#include "esp_log.h"
#include "esp_err.h"

#include <sys/socket.h>

#define HOST_IP "192.168.1.128"
#define PORT 6666

static const char *TAG = "KSP-Socket";

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
    
    struct sockaddr conn_addr = {
        .sa_family = AF_INET,
        .sa_data = dest_addr.sin_addr.s_addr,
    };
    int err = connect(s, conn_addr, sizeof(conn_addr));
    if (err != 0) {
        ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "Successfully connected");
    
    return ESP_OK;
}
