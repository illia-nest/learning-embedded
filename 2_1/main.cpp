#include <stdint.h>
#include <Arduino.h>

struct GpioConfig {
    uint8_t led_pin;
    uint16_t blink_delay_ms;
};

static constexpr GpioConfig led_cfg {
    .led_pin = 38,
    .blink_delay_ms = 1000
};

enum class LEDState {
  LED_OFF,
  LED_ON
};

class LED {
private:
  LEDState state;
  uint8_t gpio_num;
  uint16_t blink_delay_ms;
  uint32_t last_toggle_ms;
public:
  LED(LEDState state, uint8_t gpio_num, uint16_t blink_delay_ms) {
    this->state = state;
    this->gpio_num = gpio_num;
    this->blink_delay_ms = blink_delay_ms;
    this->last_toggle_ms = 0;
  }

  LED(const GpioConfig &cfg) {
    this->state = LEDState::LED_OFF;
    this->gpio_num = cfg.led_pin;
    this->blink_delay_ms = cfg.blink_delay_ms;
    this->last_toggle_ms = 0;
  }

public:
  void init(uint8_t mode) {
    pinMode(this->gpio_num, mode);
  }

  void set(uint8_t val) {
    if (val == 0) {
      this->state = LEDState::LED_OFF;
    } else {
      this->state = LEDState::LED_ON;
    }

    digitalWrite(gpio_num, val);
  }

  LEDState getState() {
    return this->state;
  }

  void blink() {
    uint32_t now = millis();

    if ((now - this->last_toggle_ms) >= this->blink_delay_ms) {
      LEDState current_state = getState();
      if (current_state == LEDState::LED_ON) {
        digitalWrite(this->gpio_num, LOW);
        this->state = LEDState::LED_OFF;
      } else {
        digitalWrite(this->gpio_num, HIGH);
        this->state = LEDState::LED_ON;
      }
      this->last_toggle_ms = now;
    }
  }
};

LED& getLed() { // to avoid global LED class
    static LED led(led_cfg);
    return led;
}

void setup() {
  getLed().init(OUTPUT); // can't init LED as is, because it will be out of scope for loop()
}

void loop() {
  getLed().blink();                     
}
