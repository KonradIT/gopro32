# Camera32 - GoPro BLE API for ESP32 boards

## Examples:


### Guardian

[Guardian](examples/guardian.ino): The ESP32 will beep whenever the GoPro's BLE connection disconnects, this can happen because **it's out of range** or because the **battery died.**

**Usage**:

- Load code onto ESP32 and supply power
- Connect your camera to your phone
- Go to Settings > Bluetooth devices > connect
- Find camera32 and connect
- By now the blue LED should be off
- Turn WiFi off on the camera
- Turn WiFi on, now there should be a sub-menu that says "camera32: connected"

That's it! Now if the camera disconnects it will beep (if you have the buzzer connected) or it will turn on the blue LED

**Wiring:**

![](https://i.imgur.com/w518ZUL.png)

Connect the PWM Buzzer [like so](https://techtutorialsx.com/2017/07/01/esp32-arduino-controlling-a-buzzer-with-pwm/)

PIN 2 is for build in LED (change it according to your board), PIN 13 is for buzzer

## Bluetooth LE Remote API:

TODO EXAMPLE


````
uint16_t WiFiOn[] = {17, 01, 01};
uint16_t WiFiOff[] = {17, 01, 00};
uint16_t RecordStart[] = {01, 01, 01};
uint16_t RecordStop[] = {01, 01, 00};
uint16_t ModeVideo[] = {02, 01, 00};
uint16_t ModePhoto[] = {02, 01, 01};
uint16_t ModeMultiShot[] = {02, 01, 02};
````
