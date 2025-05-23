#include <Arduino.h>

#include "analogblinker.h"

// ****************************************************************************
// ************************** analogblinker ************************************
// ****************************************************************************

void analogblinker::init(uint8_t _pin1, uint8_t _pin2, uint16_t _blinkTime, uint8_t _polltime, bool _sync, bool _enable)
{
    pin1 = _pin1;
    pin2 = _pin2;
    blinkTime = _blinkTime;
    polltime = _polltime;
    sync = _sync;
    enable = _enable;
}

void analogblinker::poll()
{
    if (!enable)
    {
        analogWrite(pin1, 1);
        analogWrite(pin2, 1);
        return;
    }
    else
    {
        if (millis() - lastpoll > polltime)
        {
            step = 256 / (blinkTime / polltime);
            dutycycle += step;
            if (dutycycle >= 511)
            {
                dutycycle = 0;
            }
            uint16_t pwm = dutycycle > 255 ? 511 - dutycycle : dutycycle;
            analogWrite(pin1, pwm);
            if (sync)
                analogWrite(pin2, pwm);
            else
                analogWrite(pin2, 255 - pwm);
            lastpoll = millis();
        }
    }
}
void analogblinker::setblinktime(uint16_t bt)
{
    if (bt <= 1000 && bt > 50) // Wert zwischne 10 sek und 0
        blinkTime = bt;
    else
        Serial.print(" Wrong Value ( 0-10000 ms )");
}