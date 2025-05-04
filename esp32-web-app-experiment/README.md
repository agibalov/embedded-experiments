# esp32-web-app-experiment

A web app hosted by ESP32.

## How to do things

* `pushd esp32-frontend && npm run build && popd` - to build the front end
* `pio run -t uploadfs && WIFI_SSID="<Wifi SSID here>" WIFI_PASSWORD="<Wifi password here>" pio run -t upload -t monitor` - to build and run

## mDNS

The device also advertises itself on mDNS as `helloesp32.local`. On Ubuntu/Chrome, when you go to `http://helloesp32.local`, it should work.

Also, on Ubuntu install `avahi-utils`:

```
sudo apt install avahi-utils
```

Then run:

```
avahi-browse -a
``` 

to list everything mDNS has:

```
...
+ wlp7s0 IPv4 helloesp32                                    Web Site             local
...
```

Then run:

```
avahi-browse -ar | grep -A10 helloesp32.local
```

to list `helloesp32.local` details:

avahi-browse -ar | grep -A10 helloesp32.local

```
...
   hostname = [helloesp32.local]
   address = [192.168.18.176]
   port = [80]
   txt = ["message=hello world"]
...
```
