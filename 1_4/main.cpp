#include <Arduino.h>
#define RED_LED 5 
#define BLUE_LED 6
#define BUTTON_1 0
#define BUTTON_2 21

int debounceDelay = 25;
int fastDelay = 200;
int baseDelay = 2000;
int slowDelay = 2000;


void checkForChangeDelay(int buttonRead, int button, int delayTime){
    if(buttonRead == LOW){
    delay(debounceDelay);
    int stableRead = digitalRead(button);
    if(stableRead == LOW){
      baseDelay = delayTime;
      Serial.printf("Button %i is pressed.\n", button);
    }
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  Serial.begin(115200);
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  int buttonOneRead = digitalRead(BUTTON_1);  // HIGH not pressed; LOW pressed
  int buttonTwoRead = digitalRead(BUTTON_2);  // HIGH not pressed; LOW pressed

  checkForChangeDelay(buttonOneRead, BUTTON_1, slowDelay);
  checkForChangeDelay(buttonTwoRead, BUTTON_2, fastDelay);

  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(baseDelay);                      // wait for a second

  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(baseDelay);                      // wait for a second
}
