#include <Arduino.h>
#include <Stepper.h>

const int stepsPerRevolution = 32 * 64;
Stepper stepper(stepsPerRevolution, 14, 26, 27, 25);

void setup() {
  stepper.setSpeed(13);
}

void loop() {
  stepper.step(stepsPerRevolution);
  delay(1000);
  stepper.step(-stepsPerRevolution);
  delay(1000);  
}
