#ifndef ANALONGBLINKER_H
#define ANALONGBLINKER_H


#include <Arduino.h>
class analogblinker
{
public:
    bool sync = false, enable = false;
    uint8_t step = 0, polltime = 0;
   

    // PinNr1, PinNr2, Blinkzeit[ms], Abfrage-Zeit[ms], Sync-Modus, Enable[T/F]
    void init(uint8_t, uint8_t, uint16_t, uint8_t, bool, bool);
    void poll();
    void setblinktime(uint16_t );

private:
    unsigned long lastpoll = 0;
    uint8_t pin1 = 0, pin2 = 0;
    uint16_t dutycycle = 0,blinkTime = 0;
};



#endif