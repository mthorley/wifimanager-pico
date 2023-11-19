#include <Arduino.h>
#include "WiFiManager.h"

void setup() {
    WiFiManager wm("ssid", "password");
    wm.autoConnect();
}

void loop() {

}
