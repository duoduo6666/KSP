#include "esp_err.h"

#include <sys/socket.h>

esp_err_t socket_init();
esp_err_t socket_send_msg(uint8_t *msg, size_t len);
esp_err_t socket_recv_byte(uint8_t *byte);
esp_err_t socket_recv_data(uint8_t *buf, size_t len);
