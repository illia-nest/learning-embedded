#include "traffic_lights.h"
#include "stdint.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static struct traffic_lights_t{
    esp_timer_handle_t timer;
    traffic_state_t state;
    gpio_num_t red_pin;
    gpio_num_t yellow_pin;
    gpio_num_t green_pin;
    bool blinking;
}traffic_lights;

static inline void IRAM_ATTR set_traffic_lights(uint8_t red, uint8_t yellow, uint8_t green) {
    gpio_set_level(traffic_lights.red_pin, red);
    gpio_set_level(traffic_lights.yellow_pin, yellow);
    gpio_set_level(traffic_lights.green_pin, green);
}

static void IRAM_ATTR traffic_lights_timer_cb(void *arg) {
    if (!traffic_lights.blinking) {
        switch (traffic_lights.state)
        {
        case STATE_RED:
            set_traffic_lights(1, 1, 0);
            traffic_lights.state = STATE_RED_YELLOW;
            esp_timer_start_once(traffic_lights.timer, TIME_RED_YELLOW * 1000);
            ESP_LOGI("TRAFFIC_LIGHT", "STATE_RED_YELLOW");
            break;
        case STATE_RED_YELLOW:
            set_traffic_lights(0, 0, 1);
            traffic_lights.state = STATE_GREEN;
            esp_timer_start_once(traffic_lights.timer, TIME_GREEN * 1000);
            ESP_LOGI("TRAFFIC_LIGHT", "STATE_GREEN");
            break;
        case STATE_GREEN:
            set_traffic_lights(0, 1, 0);
            traffic_lights.state = STATE_YELLOW;
            esp_timer_start_once(traffic_lights.timer, TIME_YELLOW * 1000);
            ESP_LOGI("TRAFFIC_LIGHT", "STATE_YELLOW");
            break;
        case STATE_YELLOW:
            set_traffic_lights(1, 0, 0);
            traffic_lights.state = STATE_RED;
            esp_timer_start_once(traffic_lights.timer, TIME_RED * 1000);
            ESP_LOGI("TRAFFIC_LIGHT", "STATE_RED");
            break;
        default:
            break;
        }
    } else {
        if (traffic_lights.state == STATE_BLINKING_ON) {
            set_traffic_lights(0, 1, 0);
            traffic_lights.state = STATE_BLINKING_OFF;
        } else {
            set_traffic_lights(0, 0, 0);
            traffic_lights.state = STATE_BLINKING_ON;
        }
        ESP_LOGI("TRAFFIC_LIGHT", "STATE_BLINKING");
        esp_timer_start_once(traffic_lights.timer, TIME_BLINK * 1000);
    }
}

void start_traffic_lights(void) {
    esp_timer_start_once(traffic_lights.timer, TIME_RED * 1000);
}

void enable_blinking_mode(bool state) {
    if (traffic_lights.blinking == state) return;
    traffic_lights.blinking = state;
    if (!state) {
        traffic_lights.state = STATE_RED;
    } else {
        traffic_lights.state = STATE_BLINKING_ON;
    }
    traffic_lights_timer_cb(NULL);
}

esp_err_t init_traffic_lights(gpio_num_t red, gpio_num_t yellow, gpio_num_t green) {
    traffic_lights.red_pin = red;
    traffic_lights.yellow_pin = yellow;
    traffic_lights.green_pin = green;
    traffic_lights.state = STATE_RED;
    traffic_lights.blinking = false;

    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << red) | (1ULL << yellow) | (1ULL << green),
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };

    if (gpio_config(&io_conf) != ESP_OK) {
        return ESP_FAIL;
    }

    const esp_timer_create_args_t long_press_args = {
        .callback = traffic_lights_timer_cb,
        .name = "traffic_lights_timer_cb"
    };

    if (esp_timer_create(&long_press_args, &traffic_lights.timer) != ESP_OK) {
        return ESP_FAIL;
    }
    return ESP_OK;
}