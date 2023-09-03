#include "esp_log.h"
#include "esp_err.h"

#include "led.h"
#include "wifi.h"
#include "socket.h"
#include "krpc.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int clamp(int num, int limit1, int limit2) {
    int min_limit = (limit1 < limit2) ? limit1 : limit2;
    int max_limit = (limit1 > limit2) ? limit1 : limit2;

    if (num < min_limit)
        return min_limit;
    else if (num > max_limit)
        return max_limit;
    else
        return num;
}

struct _PID_t{
    float kp;
    float ki;
    float kd;
    float integral_output_limit;
    float integral;
    float error_prev;
};
typedef struct _PID_t PID_t;

float PID_update(PID_t *pid, float error, float dt){
    float p = error * pid->kp;
    pid->integral += error * dt * pid->ki;
    pid->integral = clamp(pid->integral, pid->integral_output_limit, -pid->integral_output_limit);
    float i = pid->integral;
    float d = (error - pid->error_prev) / dt * pid->kd;
    pid->error_prev = error;
    return p + i + d;
}

void app_main(void){
    ESP_ERROR_CHECK(LED_init());
    ESP_ERROR_CHECK(LED_set_pixel(1, 1, 0));
    ESP_ERROR_CHECK(LED_open());

    ESP_ERROR_CHECK(wifi_sta_init());
    ESP_ERROR_CHECK(socket_init());
    ESP_ERROR_CHECK(LED_set_pixel(0, 1, 0));
    ESP_ERROR_CHECK(krpc_connect());
    ESP_ERROR_CHECK(krpc_GetStatus());

    PID_t pid = {
        .kp = 0.1,
        .ki = 0.0,  // Corrected initialization
        .kd = 0.2,  // You might want to initialize .kd as well
        .integral_output_limit = 1,
        .integral = 0,
        .error_prev = 0,
    };

    while (true)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS); // 等待1秒钟
    }
    
}
