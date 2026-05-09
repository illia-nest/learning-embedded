#include <Arduino.h>

constexpr uint8_t BUTTON = 7;

int16_t counter = 0;
uint32_t lastInterruptTime = 0;
uint16_t lastCounter = -1;

constexpr uint32_t DEBOUNCE_MS = 20;

void IRAM_ATTR reactionOnFalling() {
  uint32_t currentTime = millis();

  if (currentTime - lastInterruptTime > DEBOUNCE_MS){
    counter++;
    lastInterruptTime = currentTime;
  }
}


void IRAM_ATTR reactionOnRising() {
  uint32_t currentTime = millis();

  if (currentTime - lastInterruptTime > DEBOUNCE_MS){
    lastInterruptTime = currentTime;
  }
}


void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(115200);
  delay(2000);
  Serial.println("Ready to rock!");
  attachInterrupt(digitalPinToInterrupt(BUTTON), reactionOnRising, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON), reactionOnFalling, FALLING);

}

void loop() {
  // друкуємо, якщо щось змінилось
  if (counter != lastCounter) {
    lastCounter = counter;

    Serial.printf("Button Pressed! Counter : %i\n", counter);
    delay(10);
  }
}