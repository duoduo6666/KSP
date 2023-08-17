#include "esp_log.h"
#include "esp_err.h"

#include "led.h"

void app_main(void){
    ESP_ERROR_CHECK(LED_init());
    ESP_ERROR_CHECK(LED_set_pixel(0, 1, 0));
    ESP_ERROR_CHECK(LED_open());
}
