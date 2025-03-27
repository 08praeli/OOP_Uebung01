#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>

class button
{
    // Member-Variable(n)
public:
    bool in, db_vorher, out, vorher = false;
    // Methode(n)
    // Pin-Nummer, Debounce-Zeit [ms], Zeitgrenze für langen Druck [ms]
    void init(uint8_t, uint8_t, uint16_t);

    void poll();

    void debounce();
    void flanke();
    void check_longpress();
    bool pos, neg = false;
    bool longpress = false;

private:
    unsigned long last = 0;
    unsigned long last_rising = 0;
    uint8_t taster;
    uint8_t debounce_time;
    uint16_t longpress_time = 1000;
};

#endif