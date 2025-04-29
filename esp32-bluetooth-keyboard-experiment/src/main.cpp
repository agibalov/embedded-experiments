#include <Arduino.h>
#include <BleKeyboard.h>

const int PREVIOUS_TRACK_PIN = 13; // red
const int NEXT_TRACK_PIN = 14; // blue
const int VOLUME_DOWN_PIN = 15; // yellow
const int VOLUME_UP_PIN = 4; // green

unsigned long lastPushTime = 0;

BleKeyboard bleKeyboard("Agibalov Kbrd", "Agibalov", 100);

void handleButtonPush();

struct Button {
  int pin;
  std::string name;
  void (*handlePush)();
};

Button buttons[] = {
  Button{13, "Previous track", []() {
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
  }},
  Button{14, "Next track", []() {
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
  }},
  Button{15, "Volume down", []() {
    bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
  }},
  Button{4, "Volume up", []() {
    bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
  }}
};

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();

  for (auto& button : buttons) {
    pinMode(button.pin, INPUT_PULLUP);
  }

  for (auto& button : buttons) {
    attachInterrupt(button.pin, handleButtonPush, FALLING);
  }
}

void handleButtonPush() {
  auto time = millis();
  if (time - lastPushTime < 200) {
    return;
  }

  lastPushTime = time;

  for (auto& button : buttons) {
    if (digitalRead(button.pin) == HIGH) {
      continue;
    }
    
    Serial.printf("Button \"%s\" pressed! %d\n", button.name.c_str(), millis());
    button.handlePush();
    break;    
  }
}

auto isConnected = false;

void loop() {
  if (!isConnected && bleKeyboard.isConnected()) {
    Serial.println("Connected!");
    isConnected = true;
  }

  delay(100);
}
