#ifndef DIGITALBLINKER_H
#define DIGITALBLINKER_H

#include <Arduino.h>

class digitalblinker
{
    private:
    unsigned long last = 0;
    uint8_t led1;
    uint8_t led2;
    bool state = false;
    unsigned long blinktime = 1000;

    public:
    bool enable = false;

    // Enable[T/F], Blinkzeit[ms], PinNr1, PinNr2
    void init(bool, unsigned long, uint8_t, uint8_t);
    void poll();
    void setblinktime(uint16_t);
};
#endif