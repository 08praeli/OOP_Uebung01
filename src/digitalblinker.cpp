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
        digitalWrite(led2, LOW);
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
void digitalblinker::setblinktime(uint16_t bt)
{
    if (bt <= 1000 && bt > 0) // Wert zwischne 10 sek und 0
        blinktime = bt;
    else
        Serial.print(" Wrong Value ( 0-10000 ms )");
}