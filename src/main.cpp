#include <ESP8266React.h>
#include <StreamServer.h>
#include <LightMqttSettingsService.h>
#include <LightStateService.h>
#include <display.h>

#define SERIAL_BAUD_RATE 115200

StreamServer serialServer;
AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightMqttSettingsService lightMqttSettingsService =
    LightMqttSettingsService(&server, esp8266React.getFS(), esp8266React.getSecurityManager());
LightStateService lightStateService = LightStateService(&server,
                                                        esp8266React.getSecurityManager(),
                                                        esp8266React.getMqttClient(),
                                                        &lightMqttSettingsService);

void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin();

  // start the ser2net server
  serialServer.setup();

  // load the initial light settings
  lightStateService.begin();

  // start the light service
  lightMqttSettingsService.begin();

  // start the server
  server.begin();

#if defined(M5STICKC) || defined(M5STICKCPLUS)
  displaySetup();
#endif
}

void loop() {
  // run the framework's loop function
  esp8266React.loop();
  serialServer.loop();

#if defined(M5STICKC) || defined(M5STICKCPLUS)
  displayLoop();
#endif  
}
