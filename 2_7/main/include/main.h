#include <stdio.h>
#include "esp_log.h"
#include "esp_timer.h"
#include "traffic_lights.h"

#define BUTTON_PIN GPIO_NUM_40

typedef enum {
    IDLE,
    HOLDING,
    DEBOUNCE,
    SHORT_PRESS,
    LONG_PRESS,
} state_t;

typedef struct {
    esp_timer_handle_t debounce_timer;
    esp_timer_handle_t long_press_timer;
    state_t state;
} button_handler_t;

typedef void (*button_callback_t)(void*);

extern button_handler_t button_handler;

button_callback_t get_long_timer_callback();
button_callback_t get_short_timer_callback();
button_callback_t get_button_callback();
state_t  get_state();
void reset_state();