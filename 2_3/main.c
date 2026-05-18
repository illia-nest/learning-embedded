#include <stdio.h>
#include "driver/gpio.h"
#include "esp_timer.h"


#define LED_1 GPIO_NUM_35
#define LED_2 GPIO_NUM_36
#define LED_3 GPIO_NUM_37


void app_main(void) {

    gpio_reset_pin(LED_1);
    gpio_reset_pin(LED_2);
    gpio_reset_pin(LED_3);

    gpio_set_direction(LED_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_3, GPIO_MODE_OUTPUT);

    uint32_t prev_time_1 = 0;
    uint32_t prev_time_2 = 0;
    uint32_t prev_time_3 = 0;

    uint8_t state = 0;

    while(1) {
        uint32_t current_time = (uint32_t)(0xFFFFFFFFu & esp_timer_get_time() / 1000);

        if (current_time - prev_time_1 >= 500) {
            prev_time_1 = current_time;
            state ^= 0b1u;
            gpio_set_level(LED_1, state & 0b1u);
        }

        if (current_time - prev_time_2 >= 700) {
            prev_time_2 = current_time;
            state ^= 0b10u;
            gpio_set_level(LED_2, state & 0b10u);
        }

        if (current_time - prev_time_3 >= 1100) {
            prev_time_3 = current_time;
            state ^= 0b100u;
            gpio_set_level(LED_3, state & 0b100u);
        }
    }
}