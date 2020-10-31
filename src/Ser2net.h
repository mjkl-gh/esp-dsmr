#ifndef Ser2netService_h
#define Ser2netService_h

#include <AsyncTCP.h>
#include <WiFi.h>

#define RX_PIN 26

class Ser2netService {
 public:
  bool serviceOn;

  static void read(ServiceState& settings, JsonObject& root) {
    root["service_on"] = settings.serviceOn;
  }

  static StateUpdateResult update(JsonObject& root, ServiceState& ServiceState) {
    boolean newState = root["led_on"] | DEFAULT_LED_STATE;
    if (lightState.ledOn != newState) {
      lightState.ledOn = newState;
      return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }

  static void haRead(LightState& settings, JsonObject& root) {
    root["state"] = settings.ledOn ? ON_STATE : OFF_STATE;
  }

  static StateUpdateResult haUpdate(JsonObject& root, LightState& lightState) {
    String state = root["state"];
    // parse new led state 
    boolean newState = false;
    if (state.equals(ON_STATE)) {
      newState = true;
    } else if (!state.equals(OFF_STATE)) {
      return StateUpdateResult::ERROR;
    }
    // change the new state, if required
    if (lightState.ledOn != newState) {
      lightState.ledOn = newState;
      return StateUpdateResult::CHANGED;
    }
    return StateUpdateResult::UNCHANGED;
  }
};
#endif    


#include <HttpEndpoint.h>
#include <FSPersistence.h>

#ifndef FACTORY_SER2NET_ENABLED
#define FACTORY_SER2NET_ENABLED true
#endif

#ifndef FACTORY_SER2NET_RX_PIN 
#define FACTORY_SER2NET_RX_PIN 26
#endif

#define SER2NET_SETTINGS_FILE "/config/ser2netSettings.json"
#define SER2NET_SETTINGS_SERVICE_PATH "/rest/ser2netSettings"


class Ser2netSettings {
 public:
  bool enabled;
  String rxPin;

  static void read(Ser2netSettings& settings, JsonObject& root) {
    root["enabled"] = settings.enabled;
    root["rxPin"] = settings.rxPin;
  }

  static StateUpdateResult update(JsonObject& root, Ser2netSettings& settings) {
    settings.enabled = root["enabled"] | FACTORY_SER2NET_ENABLED;
    settings.rxPin = root["rxPin"] | FACTORY_SER2NET_RX_PIN;
    return StateUpdateResult::CHANGED;
  }
};

class Ser2netSettingsService : public StatefulService<Ser2netSettings> {
 public:
  Ser2netSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager);

  void begin();

 private:
  FSPersistence<NTPSettings> _fsPersistence;

#ifdef ESP32
  void onStationModeGotIP(WiFiEvent_t event, WiFiEventInfo_t info);
  void onStationModeDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);
#elif defined(ESP8266)
  WiFiEventHandler _onStationModeDisconnectedHandler;
  WiFiEventHandler _onStationModeGotIPHandler;

  void onStationModeGotIP(const WiFiEventStationModeGotIP& event);
  void onStationModeDisconnected(const WiFiEventStationModeDisconnected& event);
#endif
  void configureNTP();
  void configureTime(AsyncWebServerRequest* request, JsonVariant& json);
};

#endif  // end NTPSettingsService_h