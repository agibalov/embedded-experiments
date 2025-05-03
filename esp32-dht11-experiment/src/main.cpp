#include <Arduino.h>
#include <DHTesp.h>
#include <LiquidCrystal_I2C.h>

DHTesp dhtEsp;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  
  dhtEsp.setup(13, DHTesp::DHT11);

  Wire.begin(25, 26);
  lcd.init();
  lcd.backlight();
}

void loop() {
  auto temperatureAndHumidity = dhtEsp.getTempAndHumidity();
  if (dhtEsp.getStatus() != 0) {
    Serial.printf("Error: %s\n", dhtEsp.getStatusString());
  } else {
    Serial.printf("temperature=%f humidity=%f\n", temperatureAndHumidity.temperature, temperatureAndHumidity.humidity);

    lcd.setCursor(0, 0);
    lcd.printf("Temp: %.1f C", temperatureAndHumidity.temperature);

    lcd.setCursor(0, 1);
    lcd.printf("Humidity: %.0f%%", temperatureAndHumidity.humidity);
  }

  delay(1000);
}
