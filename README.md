# WiFiManager for RaspberryPi PicoW

This library provides a captive portal similar to ESP32 WiFiManager implementations to allow WiFi credentials to be entered and stored in EEPROM so that devices can be configured to local WiFi networks.

Features
 - Basic customisable HTML content
 - Persistent storage of credentials in EEPROM 

It does not support OTA nor device configuration outside of WiFi credentials.

## Basic Usage

To create a captive portal:

    // Connect using saved creds, or start captive portal if none found. 
    // Blocks until connected or the portal is closed

    WiFiManager wm("ap_SSID", "ap_password");   // Access point credentials for portal
    bool success = wm.autoConnect();

By default, the portal appears as below. However, some basic customisation is available for the main (hero) image, title and maker attribution:

    const char main_img[] PROGMEM = R"=====(
        data:image/png;base64, ..."
    )=====";

    String title("Cool device");
    String name("DeviceName"):
    String shortname("TLA");
    String maker("Person");
    String version("1.0");
    wm.setContentText(title, name, shortname, maker, version);
    wm.setContentMainImage(main_img);
    bool success = wm.autoConnect();

where `main_img` is a char* to a base64 encoded image in this case.

## Captive Portal

Following a similar approach to the ESP WiFiManager, if no WiFi credentials are found within EEPROM, the PicoW creates an access point with an SSID of and password of chosing. Once connected a captive portal is presented enabling selection of found WiFi networks and password to be entered. Once validated, these credentials are saved in EEPROM and used to connect on next restart.

The portal home page confirms the device attributes including name, maker and firmware version.

Whilst the captive portal has been tested on iOS, Android and macOS, windows has not. If the portal does not show, entering `http://picow.local` into the browser will pull it up.

<img src="./docs/portal-root.png" alt="Captive Portal Home" width="400"/>

The portal WiFi page allows configuration of the target network.

<img src="./docs/portal-wifi.png" alt="Captive Portal WiFi setup" width="400"/>

WiFi credentials can be erased using the AdminUI which will cause the captive portal to be presented on device restart.

## Content

The templates for the captive portal web assets (e.g. HTML, CSS, images) are defined in [WiFiManagerAssets.h](./src/WiFiManagerAssets.h) where web assets or fragments of HTML are stored as `PROGMEM` variables within flash. These variables are then consumed within [WiFiManager.cpp](./src/WiFiManager.cpp) to hydrate the web assets and perform any dynamic text or style substitutiions using `String` to replace `${variable_name}` with content.

The web assets are derived from web content held under [html](./html). These web assets can be extended and tested in isolation before being encoded into `PROGMEM` variables.

Note the use of EEPROM (used to store WiFi credentials) is [simulated](https://arduino-pico.readthedocs.io/en/latest/eeprom.html), since the Raspberry Pi Pico RP2040 does not come with an EEPROM onboard, it is simulated by using a single 4K chunk of flash at the end of flash space.

## Attribution

Hero image is a nod to the excellent [OXRS ecosystem](https://oxrs.io/).
