#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "liquidcrystal_i2c_library_experiment.h"

const int SDA_PIN = 13;
const int SCL_PIN = 14;

LiquidCrystalI2CLibraryExperiment experiment(SDA_PIN, SCL_PIN, 0x27);

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  Wire.begin(SDA_PIN, SCL_PIN);
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.printf("Found I2C device at %02X\n", address);
    }
    delay(5);
  }

  Serial.println("Finished scanning");

  experiment.setUp();
}

void loop() {  
  experiment.loop();
}
