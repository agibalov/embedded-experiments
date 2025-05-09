# esp32-ota-updates-experiment

An ArduinoOTA hello world.

## How to make things happen

Launch 2 terminals - A and B.

In terminal A, upload the first version of the fs and firmware via USB, and start monitoring:

```
pio run -e esp32-usb \
    -t uploadfs

WIFI_SSID="<SSID>" \
WIFI_PASSWORD="<PASSWORD>" \
pio run -e esp32-usb \
    -t upload \
    -t monitor
```

(pay attention to the contents of `1.txt` that it prints)

Device will announce itself via mDNS as `esp32-ota-tester.local`.

Make changes to `data/1.txt`, and in terminal B upload an updated version over-the-air:

```
OTA_PASSWORD="qwerty" \
pio run -e esp32-ota \
    -t uploadfs \
    --upload-port esp32-ota-tester.local
```

While this command is running, you may want to switch to terminal A and see how the progress changes. Eventually device will restart and display the updated contents of `/1.txt`.

Then make changes to the app code (add an extra "print" somewhere). From terminal B, upload the updated firmware:

```
WIFI_SSID="<SSID>" \
WIFI_PASSWORD="<PASSWORD>" \
OTA_PASSWORD="qwerty" \
pio run -e esp32-ota \
    -t upload \
    --upload-port esp32-ota-tester.local
```

Again, switch to terminal A and see your changes after device reboots.
