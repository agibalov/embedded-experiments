#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <Esp.h>
#include <ESPmDNS.h>

// This fixes the conflict with Arduino.h
#undef B1
#include <fmt/core.h>

bool connectToWifi();
void sendHttpRequest();
void startMdns();
void startWebServer();
void showFileSystemInfo();

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

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

  startMdns();

  startWebServer();
}

void loop() {
  ws.printfAll("Server: uptime is %d\n", millis());
  delay(3000);
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

void startMdns() {
  const char* mdnsHostName = "helloesp32";
  if (MDNS.begin(mdnsHostName)) {
    MDNS.addService("http", "tcp", 80);
    MDNS.addServiceTxt("http", "tcp", "message", "hello world");

    Serial.printf("Web server should be available at: %s.local\n", mdnsHostName);
  } else {
    Serial.printf("Failed to start MDNS\n");
  }
}

void startWebServer() {
  server.addMiddleware([](AsyncWebServerRequest* request, ArMiddlewareNext next) {
    Serial.printf("Request from %s: %s %s\n", 
      request->client()->remoteIP().toString().c_str(), 
      request->methodToString(), 
      request->url().c_str());

    next();
  });

  server.on("/api/system", HTTP_GET, [](AsyncWebServerRequest* request) {
    JsonDocument doc;
    doc["chipModel"] = ESP.getChipModel();
    doc["chipRevision"] = ESP.getChipRevision();
    doc["cores"] = ESP.getChipCores();
    doc["cpuFrequency"] = ESP.getCpuFreqMHz();
    doc["totalHeap"] = ESP.getHeapSize();
    doc["freeHeap"] = ESP.getFreeHeap();
    doc["spiffsTotalBytes"] = SPIFFS.totalBytes();
    doc["spiffsUsedBytes"] = SPIFFS.usedBytes();    
    doc["sdkVersion"] = ESP.getSdkVersion();    
    doc["uptime"] = millis();    

    std::string jsonString;
    serializeJson(doc, jsonString);

    request->send(200, "application/json", jsonString.c_str());
  });

  server.on("/api/sum", HTTP_POST, [](AsyncWebServerRequest* request) {}, NULL, 
    [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    
      JsonDocument requestBodyDoc;
      DeserializationError error = deserializeJson(requestBodyDoc, data, len);
      if (error) {        
        request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
        return;
      }

      const int a = requestBodyDoc["a"];
      const int b = requestBodyDoc["b"];
      const int result = a + b;

      JsonDocument responseBodyDoc;
      responseBodyDoc["result"] = result;    

      std::string responseBodyJsonString;
      serializeJson(responseBodyDoc, responseBodyJsonString);

      request->send(200, "application/json", responseBodyJsonString.c_str());
    });

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.onNotFound([](AsyncWebServerRequest *request) {
    if (request->method() == HTTP_GET && !request->url().startsWith("/api")) {
      request->send(SPIFFS, "/index.html", "text/html");
    } else {
      request->send(404, "text/plain", "Not found");
    }
  });

  ws.onEvent([](AsyncWebSocket *ws, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
      Serial.printf("WebSocket client connected: %u\n", client->id());
      ws->printf(client->id(), "Welcome client %u!", client->id());
      ws->printfAll("Server: client %u connected!", client->id());
    } else if (type == WS_EVT_DISCONNECT) {
      Serial.printf("WebSocket client disconnected: %u\n", client->id());
      ws->printfAll("Server: client %u disconnected!", client->id());
    } else if (type == WS_EVT_DATA) {
      Serial.printf("WebSocket data received from client %u: %.*s\n", client->id(), len, data);
      ws->printfAll("Server: client %u says: %.*s", client->id(), len, data);
    }
  });

  server.addHandler(&ws);

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
