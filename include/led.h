#include <stdint.h>

esp_err_t LED_init();
esp_err_t LED_set_pixel(uint32_t red, uint32_t green, uint32_t blue);
esp_err_t LED_open();
esp_err_t LED_close();