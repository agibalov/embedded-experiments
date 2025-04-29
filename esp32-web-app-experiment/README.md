# esp32-web-app-experiment

A web app hosted by ESP32.

## How to do things

* `pushd esp32-app && npm run build && popd`
* `pio run -t uploadfs && WIFI_SSID="<Wifi SSID here>" WIFI_PASSWORD="<Wifi password here>" pio run -t upload -t monitor` - to build and run
