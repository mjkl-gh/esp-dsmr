#include <ESP8266React.h>
#include <StreamServer.h>
#include <display.h>

AsyncWebServer server(80);
ESP8266React esp8266React(&server);

void setup() {

#if defined(M5STICKC) || defined(M5STICKCPLUS)
  displaySetup();
#endif

  // start the framework and demo project
  esp8266React.begin();

  // start the server
  server.begin();
}

void loop() {
  // run the framework's loop function
  esp8266React.loop();
#if defined(M5STICKC) || defined(M5STICKCPLUS)
    displayLoop();
#endif
}
