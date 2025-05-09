#include <Arduino.h>
#include <ArduinoOTA.h>
#include <SPIFFS.h>

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("Failed to mount SPIFFS");
    return;
  }

  String contents;
  File file = SPIFFS.open("/1.txt", "r");
  if (!file) {
    Serial.printf("/1.txt doesn't exist");
  } else {
    contents = file.readString();
    file.close();

    Serial.printf("Contents of /1.txt:\n---\n%s\n---\n", contents.c_str());
  }
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  ArduinoOTA.setHostname("esp32-ota-tester");
  ArduinoOTA.setPassword("qwerty");

  ArduinoOTA.onStart([]() {
    Serial.printf("OTA Start\n");
  });
  ArduinoOTA.onEnd([]() {
    Serial.printf("\nOTA End\n");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress * 100) / total);
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });

  ArduinoOTA.begin();
  Serial.println("Ready for OTA");
}

void loop() {
  ArduinoOTA.handle();
}
