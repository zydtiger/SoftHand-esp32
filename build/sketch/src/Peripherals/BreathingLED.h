#ifndef _BREATHING_LED_H
#define _BREATHING_LED_H

#include "LED.h"

class BreathingLED
{
private:
    bool brighter = 1;
    LED led;
    int r = 255, g = 255, b = 255;
    int breathingDuration;
    long lastUpdate = -1;

public:
    double curLevel = 0;
    BreathingLED(LED led, int breathingDuration);
    ~BreathingLED();
    void setColor(int r, int g, int b);
    LED *getRawLED();
    void update();
};

#endif