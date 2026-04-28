#include <Arduino.h>
#define RED_LED 5 
#define BLUE_LED 6 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(1000);                      // wait for a second

  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(1000);                      // wait for a second
}
