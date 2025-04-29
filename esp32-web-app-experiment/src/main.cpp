#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

// This fixes the conflict with Arduino.h
#undef B1
#include <fmt/core.h>

bool connectToWifi();
void sendHttpRequest();
void startWebServer();
void showFileSystemInfo();

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS failed");
    return;
  }

  showFileSystemInfo();

  auto connectedToWifi = connectToWifi();
  if (!connectedToWifi) {
    Serial.printf("No wifi connection - not continuing\n");
    return;
  } 

  startWebServer();
}

void loop() {
}

bool connectToWifi() {
  auto ssid = WIFI_SSID;
  auto password = WIFI_PASSWORD;

  Serial.printf("Connecting to wifi (ssid=\"%s\", password=\"%s\")...\n", ssid, password);  
  WiFi.begin(ssid, password);

  wl_status_t status;
  for (auto attempts = 10; attempts > 0; --attempts) {
    status = WiFi.status();
    if (status == WL_CONNECTED) {
      break;
    }

    Serial.printf("Connecting to wifi, status: %d\n", status);
    delay(1000);
  }

  if (status != WL_CONNECTED) {    
    Serial.printf("Failed to connect to wifi, status: %d\n", status);
    return false;
  }

  Serial.printf("Connected to wifi!\n");
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("DNS: %s\n", WiFi.dnsIP().toString().c_str());
  Serial.printf("Gateway: %s\n", WiFi.gatewayIP().toString().c_str());
  
  return true;
}

AsyncWebServer server(80);

void startWebServer() {
  server.addMiddleware([](AsyncWebServerRequest* request, ArMiddlewareNext next) {
    Serial.printf("Request from %s: %s %s\n", 
      request->client()->remoteIP().toString().c_str(), 
      request->methodToString(), 
      request->url().c_str());

    next();
  });

  /*server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    auto s = fmt::format("Hello from ESP32! Uptime: {}", millis());
    request->send(200, "text/plain", s.c_str());
  });

  server.on("/json", HTTP_GET, [](AsyncWebServerRequest* request) {
    auto uptime = millis();

    JsonDocument doc;
    doc["message"] = fmt::format("Hello from ESP32! Uptime: {}", uptime);
    doc["uptime"] = uptime;

    std::string jsonString;
    serializeJsonPretty(doc, jsonString);

    request->send(200, "text/plain", jsonString.c_str());
  });*/

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.begin();
}

void showFileSystemInfo() {
  size_t totalBytes = SPIFFS.totalBytes();
  size_t usedBytes  = SPIFFS.usedBytes();
  Serial.printf("Storage total: %u bytes, used: %u bytes\n", totalBytes, usedBytes);

  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    Serial.printf("%s (%d)\n", file.path(), file.size());
    file = root.openNextFile();
  }
}
