#include <Arduino.h>
#include "digitalblinker.h"

void digitalblinker::init(bool _enable, unsigned long _blinktime, uint8_t _led1, uint8_t _led2)
{
    blinktime = _blinktime;
    led1 = _led1;
    led2 = _led2;
    enable = _enable;
}

void digitalblinker::poll()
{
    if (!enable)
    {
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        return;
    }

    if (millis() - last > blinktime)
    {
        state = !state;
        digitalWrite(led1, state);
        digitalWrite(led2, state);
        last = millis();
    }
}