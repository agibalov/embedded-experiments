#include <Arduino.h>

const uint8_t BUZZER_PIN = 13;

void activeBuzzerDemo(); // when active buzzer is used, it's just beep-beep
void passiveBuzzerDemo(); // when passive buzzer is used, it's more fun

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  
  if (false) {
    activeBuzzerDemo();
  }
  passiveBuzzerDemo();
}

void loop() {  
}

void activeBuzzerDemo() {
  for (int j = 0; j < 2; ++j) {
    for (int i = 0; i < 3; ++i) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(10);
      digitalWrite(BUZZER_PIN, LOW);
      delay(100);
    }
    delay(500);
  }
}

void passiveBuzzerDemo() {
  const int volume = 2;

  ledcAttachPin(BUZZER_PIN, 0); // attach pin to channel 0

  for (int i : {2000, 1000, 500, 250, 125, 64, 32, 16, 8, 4}) {
    ledcSetup(0, i, 8);
    ledcWrite(0, volume);
    delay(300);
    ledcWrite(0, 0);
    delay(300);
  }

  for (int i = 0; i < 2; ++i) {
    for (float a = 0; a < 2 * PI; a += 0.1) {
      ledcSetup(0, 300 + 280 * sin(a), 8);
      ledcWrite(0, volume);
      delay(30);
    }
  }
  ledcWrite(0, 0);
}