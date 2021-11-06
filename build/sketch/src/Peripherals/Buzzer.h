#ifndef _BUZZER_H
#define _BUZZER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Buzzer
{
private:
    int freq, pin;
    bool curStatus = 0;
    long lastUpdate = -1;

public:
    Buzzer(int pin, int VCC = -1, int GND = -1, int freq = 1000);
    ~Buzzer();
    void buzz();
    void buzzFor(int ms);
};


#endif