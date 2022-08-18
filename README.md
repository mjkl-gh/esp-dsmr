# ESP-DSMR

An ESP32 based p1 port reader for dutch smart meters. Based on [React](https://reactjs.org/) front-end built with [Material-UI](https://material-ui.com/).

Designed to work with the PlatformIO IDE with [limited setup](#getting-started). Please read below for setup, build and upload instructions.

## Features

Provides many of the features required for IoT projects:

* Configurable WiFi - Network scanner and WiFi configuration screen
* Configurable Access Point - Can be continuous or automatically enabled when WiFi connection fails
* Network Time - Synchronization with NTP
* Remote Firmware Updates - Firmware replacement using OTA update or upload via UI
* Security - Protected RESTful endpoints and a secured user interface

## Getting Started

### Prerequisites

You will need the following before you can get started.

* [M5stickc(-plus)](https://shop.m5stack.com/products/m5stickc-plus-esp32-pico-mini-iot-development-kit) with our P1-hat. Or an ESP32 with your own levelshifter
* [Esphomeflasher](https://github.com/esphome/esphome-flasher/releases)

### Flashing the device

Download the right Firmware from the release page. USB is for flashing over usb OTA is for updating an existing device which we will explain [here](#updating-a-device)

Attach the M5stickc or ESP32 to your computer using an usb cable. The device will pop up as available from the dropdown of serial port

![image](https://user-images.githubusercontent.com/9350991/185467060-df3dca09-b913-4b6b-a968-0182f29e5d0c.png)

* Click browse and select the downloaded .bin file
* Click Flash esp to now flash your device!
### Setting up ESP-DSMR

#### Default access point settings

By default, the factory settings configure the device to bring up an access point on start up which can be used to configure the device:

* SSID: ESP-DSMR
* Password: esp-dsmr

#### Turning the device on and off

The device is battery powered and therefore doesn't turn off immediately once the usb connection breaks. However, it will power down once the battery is depleted. You can power up a device that was powered down by holding the on/off button (left side) for 2 secs. 

Holding the on/off button for 6 secs turns the device back off.

#### Serial settings
Serial pins should be set up correctly for the current version of P1-hats. In case they aren't, theycan be changed on the serial page -> Settings.  They should be

- rx-pin 36
- tx-pin 26

Except for 1 very specific demo-device (You know who you are) which has:

- rx-pin 26
- tx-pin 32

If you are using your own device you will know what pins you've connected the rx-pin to. For know select an unused pin for tx as the current software doesn't handle unset tx-pins

The p1 port communicates at different speeds according to your model

DSMR V2/V3 Models should operate at a baud rate of 9600. These devices are currently not supported due to to much power draw on the P1 port. We are working on an energy-saving mode to fix this

DSMR V4.x/V5.x operate at a baud rate of 115200

### Updating a device

For updating an existing device with new firmware first download the right firmware for your device. For OTA updating select the xxx-OTA.bin Afterwards visit the System -> Upload firmware page of your device. Drop the firmware inside the box shown

![image](https://user-images.githubusercontent.com/9350991/185467864-debc14d2-d3d4-4430-9a90-beb0c6f2bb58.png)

Your device should be updated and reboot after a while. This might take a while depending on your esp-dsmr's network connection


## Factory settings

The framework has built-in factory settings which act as default values for the various configurable services where settings are not saved on the file system.

### Security settings and user credentials

By default, the factory settings configure two user accounts with the following credentials: 

Username | Password
-------- | --------
admin    | admin
guest    | guest

It is recommended that you change the user credentials from their defaults better protect your device. You can do this in the user interface.


## Credits

* [rjwats](https://github.com/rjwats)     - Creating the framework this is based on
* [proddy](https://github.com/proddy)     - Setting up the github CI/CD worflow this project uses
* [oxan](https://github.com/oxan)         - Creating the Streamserver implementation

## Libraries Used

* [React](https://reactjs.org/)
* [Material-UI](https://mui.com/)
* [notistack](https://github.com/iamhosseindhv/notistack)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
* [AsyncMqttClient](https://github.com/marvinroger/async-mqtt-client)
* [Streamserver](https://gist.github.com/oxan/4a1a36e12ebed13d31d7ed136b104959)
