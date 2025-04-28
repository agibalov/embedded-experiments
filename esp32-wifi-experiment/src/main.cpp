#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

// This fixes the conflict with Arduino.h
#undef B1
#include <fmt/core.h>

void listNetworks();
bool connectToWifi();
void sendHttpRequest();
void startWebServer();

void setup() {
  Serial.begin(115200);

  listNetworks();
  auto connectedToWifi = connectToWifi();
  if (!connectedToWifi) {
    Serial.printf("No wifi connection - not continuing\n");
    return;
  }

  sendHttpRequest();
  startWebServer();
}

void loop() {
}

void listNetworks() {
  int networkCount = WiFi.scanNetworks();
  Serial.printf("Found %d networks\n", networkCount);

  for (int i = 0; i < networkCount; ++i) {
    Serial.printf("%d: %s (%d dBm)\n", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  }
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

void sendHttpRequest() {
  HTTPClient httpClient;

  httpClient.begin("https://api.github.com/zen");
  auto httpCode = httpClient.GET();
  if (httpCode > 0) {
    auto payload = httpClient.getString();
    Serial.printf("HTTP code: %d, Response: \n---\n%s\n---\n", 
      httpCode, 
      payload.c_str());
  } else {
    Serial.printf("HTTP code: %d (%s)\n", 
      httpCode, 
      httpClient.errorToString(httpCode).c_str());
  }

  httpClient.end();
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

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
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
  });

  server.begin();
}
