#ifndef CONFIG_H
#define CONFIG_H

const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* HA_URL = "http://YOUR_HA_URL:8123";
const char* HA_BEARER_TOKEN = "YOUR_LONG_LIVED_TOKEN";

const int SENSOR_UPDATE_INTERVAL = 5000; // Time in milliseconds to show each sensor

// Sensor configuration structure
struct SensorConfig {
    uint8_t displayPattern;  // 7-segment pattern for first digit
    const char* entityId;    // Home Assistant entity ID
    int minValue;            // Minimum value for the sensor
    int maxValue;            // Maximum value for the sensor
};

// 7-segment patterns: 0b12345678
// (1=dot/nothing, 2=middle, 3=top-left, 4=bottom-left,
// 5=bottom, 6=bottom-right, 7=top-right, 8=top)
struct LetterLookup {
    char letter;
    uint8_t pattern;
};

const LetterLookup LETTERS[] = {
    {'C', 0b00111001},
    {'F', 0b01110001},
    {'P', 0b01110011},
    {'S', 0b01101101},
    // Add more letters as needed
};

// Sensor configurations
const SensorConfig SENSORS[] = {
    // Example: {LETTERS[2].pattern, "sensor.example", 0, 200},
};

#endif // CONFIG_H
