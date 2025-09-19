#include "HomeAssistant.h"

HomeAssistant::HomeAssistant(const char* baseUrl, const char* bearerToken) : _baseUrl(baseUrl) {
    if (bearerToken != nullptr) {
        _bearerToken = bearerToken;
    }
}

String HomeAssistant::getEntityState(const char* entityId) {
    if (WiFi.status() != WL_CONNECTED) {
        return "WiFi not connected";
    }
    
    HTTPClient http;
    WiFiClient client;
    String url = _baseUrl + "/api/states/" + entityId;
    
    http.begin(client, url);
    
    // Add authorization header if token is provided
    if (_bearerToken.length() > 0) {
        http.addHeader("Authorization", "Bearer " + _bearerToken);
    }
    http.addHeader("Content-Type", "application/json");
    
    int httpCode = http.GET();
    String payload = "";
    
    if (httpCode == HTTP_CODE_OK) {
        payload = http.getString();
        Serial.println("HA Response: " + payload);
        
        // Extract state value from JSON response
        int stateStart = payload.indexOf("\"state\":\"") + 9;
        int stateEnd = payload.indexOf("\"", stateStart);
        if (stateStart > 8 && stateEnd > stateStart) {
            return payload.substring(stateStart, stateEnd);
        } else {
            return payload; // Return full response if parsing fails
        }
    } else {
        payload = "HTTP error: " + String(httpCode);
        Serial.println(payload);
    }
    
    http.end();
    return payload;
}
