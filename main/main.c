#include "esp_log.h"
#include "esp_err.h"

#include "led.h"
#include "wifi.h"
#include "socket.h"
#include "krpc.h"

#include "varint.pb-c.h"

static const char *TAG = "KSP-main";

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

ProtobufCBinaryData vessel, flight, control;


Krpc__Schema__Argument request_set_throttle_argument0 = KRPC__SCHEMA__ARGUMENT__INIT;
Krpc__Schema__Argument request_set_throttle_argument1 = KRPC__SCHEMA__ARGUMENT__INIT;
#define set_throttle_init() \
    Krpc__Schema__Response *response_set_throttle; \
    KRPC_CREATE_REQUEST(request_set_throttle, 1); \
    request_set_throttle_argument0.position = 0; request_set_throttle_argument0.value = control; \
    request_set_throttle_argument1.position = 1; \
    KRPC_CALL_Control_set_throttle(set_throttle, request_set_throttle, 0, request_set_throttle_argument0, request_set_throttle_argument1);
#define set_throttle(v, buf, _len) \
    encode_float(v, &buf, &_len); \
    request_set_throttle_argument1.value.data = buf+1; \
    request_set_throttle_argument1.value.len = _len-1; \
    krpc_Request(&request_set_throttle, &response_set_throttle); \
    free(buf);

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
        .kp = 0.09f,
        .ki = 0.01f,  // Corrected initialization
        .kd = 1.0f,  // You might want to initialize .kd as well
        .integral_output_limit = 1.0f,
        .integral = 0.0f,
        .error_prev = 0.0f,
    };

    KRPC_CREATE_REQUEST(request_ut, 1);
    KRPC_CALL_SpaceCenter_UT(get_ut, request_ut, 0);
    Krpc__Schema__Response *response_ut;
    krpc_Request(&request_ut, &response_ut);
    ESP_LOGI(TAG, "time: %lf", decode_double(response_ut->results[0]->value.data, response_ut->results[0]->value.len));

    KRPC_CREATE_REQUEST(request_vessel, 1);
    KRPC_CALL_SpaceCenter_ActiveVessel(get_vessel, request_vessel, 0);
    Krpc__Schema__Response *response_vessel;
    krpc_Request(&request_vessel, &response_vessel);
    vessel = response_vessel->results[0]->value;

    KRPC_CREATE_REQUEST(request_f_c, 2);
    Krpc__Schema__Argument vessel_argument = KRPC__SCHEMA__ARGUMENT__INIT;
    vessel_argument.position = 0; vessel_argument.value = vessel;
    KRPC_CALL_Vessel_Flight(get_flight, request_f_c, 0, vessel_argument);
    KRPC_CALL_Vessel_Control(get_control, request_f_c, 1, vessel_argument);
    Krpc__Schema__Response *response_f_c;
    krpc_Request(&request_f_c, &response_f_c);
    flight = response_f_c->results[0]->value;
    control = response_f_c->results[1]->value;
    
    KRPC_CREATE_REQUEST(request_SurfaceAltitude, 1);
    Krpc__Schema__Argument request_SurfaceAltitude_argument0 = KRPC__SCHEMA__ARGUMENT__INIT;
    request_SurfaceAltitude_argument0.position = 0; request_SurfaceAltitude_argument0.value = flight;
    KRPC_CALL_Flight_SurfaceAltitude(get_SurfaceAltitude, request_SurfaceAltitude, 0, request_SurfaceAltitude_argument0);
    Krpc__Schema__Response *response_SurfaceAltitude;
    krpc_Request(&request_SurfaceAltitude, &response_SurfaceAltitude);
    double high = decode_double(response_SurfaceAltitude->results[0]->value.data, response_SurfaceAltitude->results[0]->value.len);
    ESP_LOGI(TAG, "high: %lf", high);

    set_throttle_init();
    size_t len;
    uint8_t *buf; 
    // for (float i=0.01; i<=1; i+=0.01){
    //     set_throttle(i, buf, len);
    // }


    krpc_Request(&request_ut, &response_ut);
    double game_prev_time = decode_double(response_ut->results[0]->value.data, response_ut->results[0]->value.len);
    double ut;
    double game_delta_time;
    double height;
    double error;
    while (true){
        krpc_Request(&request_ut, &response_ut);
        ut = decode_double(response_ut->results[0]->value.data, response_ut->results[0]->value.len);
        game_delta_time = ut - game_prev_time;
        if (game_delta_time < 0.019){
            continue;
        }

        krpc_Request(&request_SurfaceAltitude, &response_SurfaceAltitude);
        height = decode_double(response_SurfaceAltitude->results[0]->value.data, response_SurfaceAltitude->results[0]->value.len);
        error = 10 - height;
        set_throttle(PID_update(&pid, (float)error, (float)game_delta_time), buf, len);
        ESP_LOGI(TAG, "dt=%f, error=%f" ,game_delta_time, error);
        game_prev_time = ut;
    }
    
}