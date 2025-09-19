#ifndef HOMEASSISTANT_H
#define HOMEASSISTANT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class HomeAssistant {
public:
    HomeAssistant(const char* baseUrl, const char* bearerToken = nullptr);
    String getEntityState(const char* entityId);
private:
    String _baseUrl;
    String _bearerToken;
};

#endif // HOMEASSISTANT_H
