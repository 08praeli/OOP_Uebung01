// ****************************************************************************
// *                                                                          *
// * Aufgabe:                                                                 *
// *                                                                          *
// * -> Schreib ein Programm mit folgenden Eigenschaften:                     *
// *    Es gibt zwei Taster (TASTER1, TASTER2), zwei LEDs (LED1, LED2) und    *
// *    ein Potentiometer. Taster1 schaltet einen digitalen Blinker auf die   *
// *    beiden LEDs, Taster2 schaltet einen analogen Blinker auf die beiden   *
// *    LEDs. Die Geschwindigkeit des Blinkers soll mit dem Poti zwischen     *
// *    50ms und 1000ms eingestellt werden können. Ein langer Tastendruck     *
// *    auf einen der beiden Taster toggelt die Blinkfunktion ein/aus.        *
// *                                                                          *
// * -> Suche dir ein/zwei Mitarbeiter und forke dieses Projekt               *
// * -> Teile die Arbeit auf die Mitarbeiter so auf, dass ein fast-forward-   *
// *    merge ermöglicht wird.                                                *
// * -> Fülle die bestehenden Header-Dateien und erzeuge die entsprechenden   *
// *    Implementierungen (cpp-Dateien). Verwende ausschließlich Klassen!     *
// *                                                                          *
// * -> Erstelle einen pull-request                                           *
// *                                                                          *
// *                                                                          *
// ****************************************************************************

#include <Arduino.h>
#include "analogblinker.h"
#include "digitalblinker.h"
#include "helper.h"

analogblinker ablink1;
digitalblinker dblink1;
button bt1;
button bt2;

#define LED1 5    // Low-side switch (leuchtet mit HIGH)
#define LED2 3    // Low-side switch (leuchtet mit HIGH)
#define TASTER1 2 // LOW wenn gedrückt
#define TASTER2 4 // LOW wenn gedrückt
#define POT1 A7
#define DBTIME 50
#define LONGPRESSTIME 1000

uint16_t blinktime = 50;
uint16_t potvalue;
bool enableD = false;
bool enableA = false;

void setup()
{
    pinMode(POT1, INPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(TASTER1, INPUT_PULLUP);
    pinMode(TASTER2, INPUT_PULLUP);
    Serial.begin(115200); // Baud rate
    Serial.println("..Start..\n");
    bt1.init(TASTER1,  DBTIME, LONGPRESSTIME);
    bt2.init(TASTER2,  DBTIME, LONGPRESSTIME);
    dblink1.init(0, blinktime, LED1, LED2);
    ablink1.init(LED1, LED2, blinktime, 50, false, 0);
}

void loop()
{
    ablink1.poll();
    dblink1.poll();
    bt1.poll();
    bt2.poll();
    potvalue = analogRead(POT1);

    if (bt1.longpress)
    {
        
            dblink1.enable = !dblink1.enable;
    }
    if (bt2.longpress)
    {
        
            ablink1.enable = !ablink1.enable;
    }
    ablink1.setblinktime(50 + (950 * (potvalue / 1023.0)));
    dblink1.setblinktime(50 + (950 * (potvalue / 1023.0)));
    
    Serial.println(dblink1.enable);
    Serial.println(ablink1.enable);
    Serial.println("==============");
    delay(500);

}
