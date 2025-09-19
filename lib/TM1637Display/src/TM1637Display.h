#ifndef TM1637DISPLAY_H
#define TM1637DISPLAY_H

#include <Arduino.h>

class TM1637Display {
public:
    TM1637Display(uint8_t clk, uint8_t dio);
    void setBrightness(uint8_t brightness);
    void showNumberDec(int num, bool leading_zero = false);
    void showCustomDigitAndNumber(uint8_t customPattern, int num);
    void showCustomDigitBlankAndTwoDigits(uint8_t customPattern, int num);
    void clear();
private:
    uint8_t _clk, _dio;
    void bitDelay();
    void start();
    void stop();
    bool writeByte(uint8_t b);
};

#endif
