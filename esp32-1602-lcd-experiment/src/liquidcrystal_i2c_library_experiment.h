#include <string>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class LiquidCrystalI2CLibraryExperiment {
  int sdaPin;
  int sclPin;
  LiquidCrystal_I2C lcd;
  int displayLength = -1;
  const std::string message = "Hello, world!";

public:
  LiquidCrystalI2CLibraryExperiment(int sdaPin, int sclPin, int address) 
  : sdaPin(sdaPin), sclPin(sclPin), lcd(address, 16, 2) {    
  }

  void setUp() {
    Wire.begin(sdaPin, sclPin);
    lcd.init();
    lcd.backlight();
    displayLength = 0;
  }

  void loop() {    
    if (displayLength > message.length()) {
      displayLength = 0;
      lcd.clear();
    }
    ++displayLength;
    const auto truncatedMessage = message.substr(0, displayLength);
  
    lcd.setCursor(0, 0);
    lcd.printf(truncatedMessage.c_str());
  
    lcd.setCursor(0, 1);
    lcd.printf("Uptime: %d", millis() / 1000);  
    
    delay(100);
  }
};
