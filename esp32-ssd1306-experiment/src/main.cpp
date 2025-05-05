#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "BallDemo.h"

TwoWire display1I2C = TwoWire(0);
Adafruit_SSD1306 display1(128, 64, &display1I2C, -1);
BallDemo ballDemo1(display1, "Display #1");

TwoWire display2I2C = TwoWire(1);
Adafruit_SSD1306 display2(128, 32, &display2I2C, -1);
BallDemo ballDemo2(display2, "Display #2");

void setup() {
  Serial.begin(115200);

  display1I2C.begin(13, 14);
  if(!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("Failed to initialize display1");
    return;
  }

  display2I2C.begin(21, 22);
  if(!display2.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("Failed to initialize display2");
    return;
  }
}

void loop() {  
  ballDemo1.update();
  ballDemo2.update();
}
