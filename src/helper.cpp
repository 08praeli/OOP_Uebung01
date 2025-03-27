#include <Arduino.h>
#include "helper.h"

void button::init(uint8_t _taster, bool _inv, uint8_t _debounce_time, uint16_t _longpress_time)
{
    inv = _inv;
    taster = _taster;
    debounce_time = _debounce_time;
    longpress_time = _longpress_time;
}

void button::poll()
{
    in = inv ? !digitalRead(taster) : digitalRead(taster);
    debounce();
    flanke();
    check_longpress();
}

void button::debounce()
{
    if (millis() - last > debounce_time)
    {
        if (in != db_vorher)
        {
            last = millis();
        }
        db_vorher = in;
        out = db_vorher;
    }
}

void button::flanke()
{
    pos = false;

    if (out && !vorher)
        pos = true;

    neg = false;

    if (!out && vorher)
        neg = true;

    vorher = out;
}

void button::check_longpress()
{
    longpress = false;

    if (pos)
    {
        last_rising = millis();
        return;
    }

    if (neg)
    {
        if (millis() - last_rising > longpress_time)
        {
            longpress = true;
        }
    }
}