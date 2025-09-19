# Digital Display Project

This project is designed for PlatformIO and uses a microcontroller to display sensor data from Home Assistant on a TM1637 7-segment display.

## Features
- Connects to WiFi and Home Assistant
- Fetches sensor data using REST API
- Displays values on a TM1637 4-digit display
- Configurable sensor list and display patterns

## Getting Started

### Prerequisites
- PlatformIO (VS Code extension or CLI)
- Supported microcontroller (e.g., ESP8266, ESP32)
- TM1637 4-digit display

### Setup
1. **Clone the repository:**
   ```bash
   git clone <your-repo-url>
   cd "Digital display"
   ```
2. **Configure your secrets:**
   - Copy `include/config.example.h` to `include/config.h`:
     ```bash
     cp include/config.example.h include/config.h
     ```
   - Edit `include/config.h` and fill in your WiFi, Home Assistant URL, and token.

3. **Install dependencies:**
   PlatformIO will automatically install library dependencies on build.

4. **Build and upload:**
   - Connect your device via USB.
   - Run:
     ```bash
     platformio run --target upload
     ```

5. **Monitor serial output (optional):**
   ```bash
   platformio device monitor
   ```

## File Structure
- `src/` - Main application source code
- `include/` - Configuration headers
- `lib/` - Libraries (TM1637, HomeAssistant)
- `platformio.ini` - PlatformIO project configuration

