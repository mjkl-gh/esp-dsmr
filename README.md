# ESP-DSMR

An ESP32 based p1 port reader for dutch smart meters. Based on [React](https://reactjs.org/) front-end built with [Material-UI](https://material-ui.com/).

Designed to work with the PlatformIO IDE with [limited setup](#getting-started). Please read below for setup, build and upload instructions.

## Features

Provides many of the features required for IoT projects:

* Configurable WiFi - Network scanner and WiFi configuration screen
* Configurable Access Point - Can be continuous or automatically enabled when WiFi connection fails
* Network Time - Synchronization with NTP
* MQTT - Connection to an MQTT broker for automation and monitoring
* Remote Firmware Updates - Firmware replacement using OTA update or upload via UI
* Security - Protected RESTful endpoints and a secured user interface

Features may be [enabled or disabled](#selecting-features) as required at compile time.

## Getting Started

### Prerequisites

You will need the following before you can get started.

* [PlatformIO](https://platformio.org/) - IDE for development
* [Node.js](https://nodejs.org) - For building the interface with npm

### Building and uploading the firmware

Pull the project and open it in PlatformIO. PlatformIO should download the ESP8266 platform and the project library dependencies automatically.

The project structure is as follows:

Resource                         | Description
-------------------------------- | ----------------------------------------------------------------------
[interface/](interface)          | React based front end
[lib/framework/](lib/framework)  | C++ back end for the ESP8266/ESP32 device
[src/](src)                      | The main.cpp and demo project to get you started
[scripts/](scripts)              | Scripts that build the React interface as part of the platformio build
[platformio.ini](platformio.ini) | PlatformIO project configuration file

### Building the firmware

Once the platform and libraries are downloaded the back end should successfully build within PlatformIO. 

The firmware may be built by pressing the "Build" button:

![build](/media/build.png?raw=true "build")

Alternatively type the run command:

```bash
platformio run
```

#### Uploading the firmware

The project is configured to upload over a serial connection by default. You can change this to use OTA updates by uncommenting the relevant lines in ['platformio.ini'](platformio.ini). 

The firmware may be uploaded to the device by pressing the "Upload" button:

![uploadfw](/media/uploadfw.png?raw=true "uploadfw")

Alternatively run the 'upload' target:

```bash
platformio run -t upload
```

### Building & uploading the interface

The interface has been configured with create-react-app and react-app-rewired so the build can customized for the target device. The large artefacts are gzipped and source maps and service worker are excluded from the production build. This reduces the production build to around ~150k, which easily fits on the device.

The interface will be automatically built by PlatformIO before it builds the firmware. The project can be configured to serve the interface from either PROGMEM or the filesystem as your project requires. The default configuration is to serve the content from PROGMEM, serving from the filesystem requires an additional upload step which is [documented below](#serving-the-interface-from-the-filesystem).

## Factory settings

The framework has built-in factory settings which act as default values for the various configurable services where settings are not saved on the file system. These settings can be overridden using the build flags defined in [factory_settings.ini](factory_settings.ini).

Customize the settings as you see fit, for example you might configure your home WiFi network as the factory default:

```ini
  -D FACTORY_WIFI_SSID=\"My Awesome WiFi Network\"
  -D FACTORY_WIFI_PASSWORD=\"secret\"
  -D FACTORY_WIFI_HOSTNAME=\"awesome_light_controller\"
```

### Default access point settings

By default, the factory settings configure the device to bring up an access point on start up which can be used to configure the device:

* SSID: ESP8266-React
* Password: esp-react

### Security settings and user credentials

By default, the factory settings configure two user accounts with the following credentials: 

Username | Password
-------- | --------
admin    | admin
guest    | guest

It is recommended that you change the user credentials from their defaults better protect your device. You can do this in the user interface, or by modifying [factory_settings.ini](factory_settings.ini) as mentioned above.

### Customizing the factory time zone setting

Changing factory time zone setting is a common requirement. This requires a little effort because the time zone name and POSIX format are stored as separate values for the moment. The time zone names and POSIX formats are contained in the UI code in [TZ.tsx](interface/src/ntp/TZ.tsx). Take the appropriate pair of values from there, for example, for Los Angeles you would use:

```ini
  -D FACTORY_NTP_TIME_ZONE_LABEL=\"America/Los_Angeles\"
  -D FACTORY_NTP_TIME_ZONE_FORMAT=\"PST8PDT,M3.2.0,M11.1.0\"
```

### Placeholder substitution

Various settings support placeholder substitution, indicated by comments in [factory_settings.ini](factory_settings.ini). This can be particularly useful where settings need to be unique, such as the Access Point SSID or MQTT client id. The following placeholders are supported:

Placeholder  | Substituted value 
-----------  | -----------------
#{platform}  | The microcontroller platform, e.g. "esp32" or "esp8266"
#{unique_id} | A unique identifier derived from the MAC address, e.g. "0b0a859d6816"
#{random}    | A random number encoded as a hex string, e.g. "55722f94"

You may use SettingValue::format in your own code if you require the use of these placeholders. This is demonstrated in the demo project:

```cpp
  static StateUpdateResult update(JsonObject& root, LightMqttSettings& settings) {
    settings.mqttPath = root["mqtt_path"] | SettingValue::format("homeassistant/light/#{unique_id}");
    settings.name = root["name"] | SettingValue::format("light-#{unique_id}");
    settings.uniqueId = root["unique_id"] | SettingValue::format("light-#{unique_id}");
    return StateUpdateResult::CHANGED;
  }
};
```

## Building for different devices

This project supports ESP8266 and ESP32 platforms. To support OTA programming, enough free space to upload the new sketch and file system image will be required. It is recommended that a board with at least 2mb of flash is used.

The pre-configured environments are "esp12e" and "node32s". These are common ESP8266/ESP32 variants with 4mb of flash:

![ESP12E](/media/esp12e.jpg?raw=true "ESP12E") ![ESP32](/media/esp32.jpg?raw=true "ESP32")

The settings file ['platformio.ini'](platformio.ini) configures the supported environments. Modify these, or add new environments for the devides you need to support. The default environments are as follows:

```ini
[env:esp12e]
platform = espressif8266
board = esp12e
board_build.f_cpu = 160000000L

[env:node32s]
platform = espressif32
board = node32s
```

If you want to build for a different device, all you need to do is re-configure ['platformio.ini'](platformio.ini) and select an alternative environment by modifying the default_envs variable. Building for the common esp32 "node32s" board for example:

```ini
[platformio]
;default_envs = esp12e
default_envs = node32s
```

## Customizing and theming

The framework, and MaterialUI allows for a reasonable degree of customization with little effort.

### Theming the app

The app can be easily themed by editing the [MaterialUI theme](https://material-ui.com/customization/theming/). Edit the theme in ['interface/src/CustomMuiTheme.tsx'](interface/src/CustomMuiTheme.tsx) as you desire. For example, here is a dark theme:

```js
const theme = createMuiTheme({
  palette: {
    type:"dark",
    primary: {
      main: '#222',
    },
    secondary: {
      main: '#666',
    },
    info: {
      main: blueGrey[500]
    },
    warning: {
      main: orange[500]
    },
    error: {
      main: red[500]
    },
    success: {
      main: green[500]
    }
  }
});
```

![Dark Theme](/media/dark.png?raw=true "Dark Theme")
## Back end

The back end is a set of REST endpoints hosted by a [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) instance. The ['lib/framework'](lib/framework) directory contains the majority of the back end code. The framework contains of a number of useful utility classes which you can use when extending it. The project also comes with a demo project to give you some help getting started. 

The framework's source is split up by feature, for example [WiFiScanner.h](lib/framework/WiFiScanner.h) implements the end points for scanning for available networks where as [WiFiSettingsService.h](lib/framework/WiFiSettingsService.h) handles configuring the WiFi settings and managing the WiFi connection.

### Initializing the framework

The ['src/main.cpp'](src/main.cpp) file constructs the webserver and initializes the framework. You can add endpoints to the server here to support your IoT project. The main loop is also accessable so you can run your own code easily. 

The following code creates the web server and esp8266React framework:

```cpp
AsyncWebServer server(80);
ESP8266React esp8266React(&server);
```

Now in the `setup()` function the initialization is performed:

```cpp
void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin();

  // start the server
  server.begin();
}
```

Finally the loop calls the framework's loop function to service the frameworks features.

```cpp
void loop() {
  // run the framework's loop function
  esp8266React.loop();
}
```

#### MQTT

The framework includes an MQTT client which can be configured via the UI. MQTT requirements will differ from project to project so the framework exposes the client for you to use as you see fit. The framework does however provide a utility to interface StatefulService to a pair of pub/sub (state/set) topics. This utility can be used to synchronize state with software such as Home Assistant.

[MqttPubSub.h](lib/framework/MqttPubSub.h) allows you to publish and subscribe to synchronize state over a pair of MQTT topics. MqttPubSub automatically pushes changes to the "pub" topic and reads updates from the "sub" topic.

### Security features

The framework has security features to prevent unauthorized use of the device. This is driven by [SecurityManager.h](lib/framework/SecurityManager.h).

On successful authentication, the /rest/signIn endpoint issues a [JSON Web Token (JWT)](https://jwt.io/) which is then sent using Bearer Authentication. The framework come with built-in predicates for verifying a users access privileges. The built in AuthenticationPredicates can be found in [SecurityManager.h](lib/framework/SecurityManager.h) and are as follows:

Predicate            | Description
-------------------- | -----------
NONE_REQUIRED        | No authentication is required.
IS_AUTHENTICATED     | Any authenticated principal is permitted.
IS_ADMIN             | The authenticated principal must be an admin.

You can use the security manager to wrap any request handler function with an authentication predicate:

```cpp
server->on("/rest/someService", HTTP_GET, 
  _securityManager->wrapRequest(std::bind(&SomeService::someService, this, std::placeholders::_1), AuthenticationPredicates::IS_AUTHENTICATED)
);
```

### Accessing settings and services

The framework supplies access to various features via getter functions:

SettingsService              | Description
---------------------------- | ----------------------------------------------
getFS()                      | The filesystem used by the framework
getSecurityManager()         | The security manager - detailed above
getSecuritySettingsService() | Configures the users and other security settings
getWiFiSettingsService()     | Configures and manages the WiFi network connection
getAPSettingsService()       | Configures and manages the Access Point
getNTPSettingsService()      | Configures and manages the network time
getOTASettingsService()      | Configures and manages the Over-The-Air update feature
getMqttSettingsService()     | Configures and manages the MQTT connection
getMqttClient()              | Provides direct access to the MQTT client instance

The core features use the [StatefulService.h](lib/framework/StatefulService.h) class and can therefore you can change settings or observe changes to settings through the read/update API.

Inspect the current WiFi settings:

```cpp
esp8266React.getWiFiSettingsService()->read([&](WiFiSettings& wifiSettings) {
  Serial.print("The ssid is:");
  Serial.println(wifiSettings.ssid);
});
```

Configure the WiFi SSID and password manually:

```cpp
esp8266React.getWiFiSettingsService()->update([&](WiFiSettings& wifiSettings) {
  wifiSettings.ssid = "MyNetworkSSID";
  wifiSettings.password = "MySuperSecretPassword";
  return StateUpdateResult::CHANGED; 
}, "myapp");
```

Observe changes to the WiFiSettings:

```cpp
esp8266React.getWiFiSettingsService()->addUpdateHandler(
  [&](const String& originId) {
    Serial.println("The WiFi Settings were updated!");
  }
);
```

## Credits

* [rjwats](https://github.com/rjwats)     - Creating the framework this is based on
* [proddy](https://github.com/proddy)     - Setting up the github CI/CD worflow this project uses
* [oxan](https://github.com/oxan)         - Creating the Streamserver implementation

## Libraries Used

* [React](https://reactjs.org/)
* [Material-UI](https://material-ui.com/)
* [notistack](https://github.com/iamhosseindhv/notistack)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
* [AsyncMqttClient](https://github.com/marvinroger/async-mqtt-client)
* [Streamserver](https://gist.github.com/oxan/4a1a36e12ebed13d31d7ed136b104959)
