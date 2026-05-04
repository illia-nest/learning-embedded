#include <Arduino.h>

constexpr uint8_t PHOTO_SENSOR = 4;

void setup() {
  Serial.begin(115200);
  pinMode(PHOTO_SENSOR, ANALOG);
  Serial.println("Hi");
}

void loop() {
  uint16_t sensorValue = analogRead(PHOTO_SENSOR);
  uint32_t milliVolts  = analogReadMilliVolts(PHOTO_SENSOR);
  double voltageFromSensor = sensorValue * (3.3/ 4095.0);
  double voltageFromReadMilli = milliVolts / 1000.0;
  double errorSensorMili = (voltageFromSensor - voltageFromReadMilli) / voltageFromSensor * 100;
  Serial.printf("RAW: %i\tVoltage1 (analogRead): %.4fV\tVoltage2(analogReadMilliVolts): %.4fV\tError(V1-V2): %.4f%%\n", sensorValue, voltageFromSensor, voltageFromReadMilli, errorSensorMili);
  delay(100);
}