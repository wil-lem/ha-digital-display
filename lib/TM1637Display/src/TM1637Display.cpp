// Minimal implementation for TM1637 4-digit display
#include "TM1637Display.h"

#define TM1637_CMD_SET_DATA 0x40
#define TM1637_CMD_SET_ADDR 0xC0
#define TM1637_CMD_SET_DISPLAY 0x88

static const uint8_t digitToSegment[] = {
  0x3F, // 0
  0x06, // 1
  0x5B, // 2
  0x4F, // 3
  0x66, // 4
  0x6D, // 5
  0x7D, // 6
  0x07, // 7
  0x7F, // 8
  0x6F  // 9
};

TM1637Display::TM1637Display(uint8_t clk, uint8_t dio) : _clk(clk), _dio(dio) {
    pinMode(_clk, OUTPUT);
    pinMode(_dio, OUTPUT);
    digitalWrite(_clk, HIGH);
    digitalWrite(_dio, HIGH);
}

void TM1637Display::bitDelay() {
    delayMicroseconds(50);
}

void TM1637Display::start() {
    digitalWrite(_dio, HIGH);
    digitalWrite(_clk, HIGH);
    bitDelay();
    digitalWrite(_dio, LOW);
    bitDelay();
    digitalWrite(_clk, LOW);
}

void TM1637Display::stop() {
    digitalWrite(_clk, LOW);
    bitDelay();
    digitalWrite(_dio, LOW);
    bitDelay();
    digitalWrite(_clk, HIGH);
    bitDelay();
    digitalWrite(_dio, HIGH);
}

bool TM1637Display::writeByte(uint8_t b) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(_clk, LOW);
        digitalWrite(_dio, (b >> i) & 0x01);
        bitDelay();
        digitalWrite(_clk, HIGH);
        bitDelay();
    }
    digitalWrite(_clk, LOW);
    pinMode(_dio, INPUT);
    bitDelay();
    bool ack = digitalRead(_dio) == 0;
    pinMode(_dio, OUTPUT);
    digitalWrite(_clk, HIGH);
    bitDelay();
    return ack;
}

void TM1637Display::setBrightness(uint8_t brightness) {
    start();
    writeByte(TM1637_CMD_SET_DISPLAY | (brightness & 0x07));
    stop();
}

void TM1637Display::showNumberDec(int num, bool leading_zero) {
    uint8_t data[4];
    for (int i = 3; i >= 0; i--) {
        data[i] = digitToSegment[num % 10];
        num /= 10;
    }
    start();
    writeByte(TM1637_CMD_SET_DATA);
    stop();
    start();
    writeByte(TM1637_CMD_SET_ADDR);
    for (int i = 0; i < 4; i++) {
        writeByte(data[i]);
    }
    stop();
}

void TM1637Display::showCustomDigitAndNumber(uint8_t customPattern, int num) {
    uint8_t data[4];
    
    // First digit is custom pattern
    data[0] = customPattern;
    
    // Next 3 digits are the number (limit to 3 digits: 0-999)
    num = num % 1000; // Ensure it's max 3 digits
    data[3] = digitToSegment[num % 10];
    num /= 10;
    data[2] = digitToSegment[num % 10];
    num /= 10;
    data[1] = digitToSegment[num % 10];
    
    start();
    writeByte(TM1637_CMD_SET_DATA);
    stop();
    start();
    writeByte(TM1637_CMD_SET_ADDR);
    for (int i = 0; i < 4; i++) {
        writeByte(data[i]);
    }
    stop();
}

void TM1637Display::showCustomDigitBlankAndTwoDigits(uint8_t customPattern, int num) {
    uint8_t data[4];
    
    // First digit is custom pattern
    data[0] = customPattern;
    
    // Second digit is blank
    data[1] = 0x00;
    
    // Limit number to 0-99
    if (num > 99) num = 99;
    if (num < 0) num = 0;
    
    // Last 2 digits are the number (0-99)
    data[3] = digitToSegment[num % 10];
    num /= 10;
    data[2] = digitToSegment[num % 10];
    
    start();
    writeByte(TM1637_CMD_SET_DATA);
    stop();
    start();
    writeByte(TM1637_CMD_SET_ADDR);
    for (int i = 0; i < 4; i++) {
        writeByte(data[i]);
    }
    stop();
}

void TM1637Display::clear() {
    start();
    writeByte(TM1637_CMD_SET_DATA);
    stop();
    start();
    writeByte(TM1637_CMD_SET_ADDR);
    for (int i = 0; i < 4; i++) {
        writeByte(0);
    }
    stop();
}
