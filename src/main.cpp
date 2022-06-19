#include <ESP8266React.h>
#include <StreamServer.h>
#include <LightMqttSettingsService.h>
#include <LightStateService.h>
#include <display.h>

AsyncWebServer server(80);
ESP8266React esp8266React(&server);
LightMqttSettingsService lightMqttSettingsService =
    LightMqttSettingsService(&server, esp8266React.getFS(), esp8266React.getSecurityManager());
LightStateService lightStateService = LightStateService(&server,
                                                        esp8266React.getSecurityManager(),
                                                        esp8266React.getMqttClient(),
                                                        &lightMqttSettingsService);

void setup() {
  // start the framework and demo project
  esp8266React.begin();

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
  #if defined(M5STICKC) || defined(M5STICKCPLUS)
    displayLoop();
#endif
}
