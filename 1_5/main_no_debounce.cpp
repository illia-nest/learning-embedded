#include <Arduino.h>

constexpr uint8_t BUTTON = 7;

int16_t counter = 0;

void IRAM_ATTR reaction() {
  counter++;
  Serial.println("\nButton Pressed! Count: " + String(counter));
}


void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(BUTTON), reaction, FALLING);

}

void loop() {
  Serial.printf("Counter : %i\n", counter);
  delay(250);
}