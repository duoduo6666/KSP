#include "led_strip.h"
#include "esp_log.h"
#include "esp_err.h"

// GPIO assignment
#define LED_STRIP_BLINK_GPIO  48
// Numbers of the LED in the strip
#define LED_STRIP_LED_NUMBERS 1
// 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ  (10 * 1000 * 1000)