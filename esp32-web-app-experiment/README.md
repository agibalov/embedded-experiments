# esp32-web-app-experiment

A web app hosted by ESP32.

## How to do things

* `pushd esp32-frontend && npm run build && popd` - to build the front end
* `pio run -t uploadfs && WIFI_SSID="<Wifi SSID here>" WIFI_PASSWORD="<Wifi password here>" pio run -t upload -t monitor` - to build and run
