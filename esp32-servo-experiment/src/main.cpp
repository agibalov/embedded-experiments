#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo;

void setup() {
  Serial.begin(115200);

  servo.setPeriodHertz(50);

  // these need to be adjusted for different servos
  // in my case maxTimeUs of 2500 makes it turn ~200 degrees
  const int servoPin = 15;
  const int minTimeUs = 500;
  const int maxTimeUs = 2400;
  servo.attach(servoPin, minTimeUs, maxTimeUs);

  servo.write(0);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(180);
  delay(1000);
}

int previousAngle = -1;

void loop() {  
  const int handleResolutionBits = 12;
  analogReadResolution(handleResolutionBits);

  const int handlePin = 34;
  const int maxAdcValue = (1 << handleResolutionBits) - 1;
  int input = analogRead(handlePin);
  int angle = map(input, 0, maxAdcValue, 0, 180);
  servo.write(angle);
  Serial.printf("angle: %d\n", angle);
  delay(15);
}
