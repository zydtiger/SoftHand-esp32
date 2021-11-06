#include "BreathingLED.h"

BreathingLED::BreathingLED(LED led, int breathingDuration)
    : led(led), breathingDuration(breathingDuration)
{
}

BreathingLED::~BreathingLED()
{
}

void BreathingLED::setColor(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

LED *BreathingLED::getRawLED()
{
    return &led;
}

void BreathingLED::update()
{
    if (lastUpdate == -1)
        lastUpdate = millis();

    double delta = (double)(millis() - lastUpdate) * 2 / breathingDuration;
    lastUpdate = millis();

    curLevel += brighter ? delta : -delta;

    if (curLevel >= 1)
        curLevel = 1, brighter = 0;
    else if (curLevel <= 0)
        curLevel = 0, brighter = 1;

    led.rAnalog(curLevel * r);
    led.gAnalog(curLevel * g);
    led.bAnalog(curLevel * b);
}