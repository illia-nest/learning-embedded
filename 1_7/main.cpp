#include <Arduino.h>

constexpr uint8_t PHOTO_SENSOR = 4;
constexpr uint8_t LED_PIN = 1;

uint16_t sensorValue[10] = {0};
bool isBright = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(PHOTO_SENSOR, INPUT);
  analogReadResolution(12);

  Serial.println("Hi");
}

void loop() {
  uint32_t roundedValue = 0;

  for (size_t i = 0; i < 10; i++) {
    sensorValue[i] = analogRead(PHOTO_SENSOR);
    roundedValue += sensorValue[i];
    
    Serial.print(sensorValue[i]);
    Serial.print(' ');
  }

  roundedValue /= 10;

  Serial.printf("Rounded: %lu\n", roundedValue);

  if (roundedValue > 1500 && !isBright) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("It's bright!");
    isBright = true;
  } 
  else if (roundedValue <= 1500 && isBright) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("It's dark!");
    isBright = false;
  }

  delay(1000);
}