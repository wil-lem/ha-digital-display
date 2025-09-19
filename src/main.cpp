#include <Arduino.h>
// WiFi and config
#include <ESP8266WiFi.h>
#include "config.h"
#include <TM1637Display.h>
#include <HomeAssistant.h>

// TM1637 display pins (change if needed)
#define DISPLAY_CLK D2
#define DISPLAY_DIO D3
TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);

// Global variables for sensor cycling
int currentSensorIndex = 0;
HomeAssistant ha(HA_URL, HA_BEARER_TOKEN);

void setup() {
  // Initialize Serial for output
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  int max_attempts = 20;
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < max_attempts) {
    delay(500);
    Serial.print(".");
    attempt++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Home Assistant URL: ");
    Serial.println(HA_URL);
  } else {
    Serial.println("\nWiFi connection failed.");
  }

  // Initialize display
  display.setBrightness(5);
  display.clear();
}

void loop() {
  // Get current sensor configuration
  const SensorConfig& currentSensor = SENSORS[currentSensorIndex];
  
  // Get sensor state from Home Assistant
  String state = ha.getEntityState(currentSensor.entityId);
  Serial.print("Sensor ");
  Serial.print(currentSensorIndex);
  Serial.print(" (");
  Serial.print(currentSensor.entityId);
  Serial.print(") State: ");
  Serial.println(state);
  
  // Convert state to number and calculate percentage
  float stateValue = state.toFloat();
  int displayValue = 0;
  
  if (stateValue <= currentSensor.minValue) {
    displayValue = 0; // Below minimum = 00
  } else if (stateValue >= currentSensor.maxValue) {
    displayValue = 99; // Above maximum = 99
  } else {
    // Calculate percentage: ((value - min) / (max - min)) * 100
    float percentage = ((stateValue - currentSensor.minValue) / 
                       (float)(currentSensor.maxValue - currentSensor.minValue)) * 100.0;
    displayValue = (int)percentage;
    
    // Ensure it stays within 0-99 range
    if (displayValue > 99) displayValue = 99;
    if (displayValue < 0) displayValue = 0;
  }
  
  display.showCustomDigitBlankAndTwoDigits(currentSensor.displayPattern, displayValue);
  Serial.print("Raw value: ");
  Serial.print(stateValue);
  Serial.print(" | Range: ");
  Serial.print(currentSensor.minValue);
  Serial.print("-");
  Serial.print(currentSensor.maxValue);
  Serial.print(" | Display: ");
  Serial.print(displayValue);
  Serial.println("%");

  // Move to next sensor
  currentSensorIndex = (currentSensorIndex + 1) % SENSOR_COUNT;

  delay(SENSOR_UPDATE_INTERVAL); // Show each sensor for 3 seconds
}
