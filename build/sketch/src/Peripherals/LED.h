#ifndef _LED_H
#define _LED_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class LED
{
private:
    bool negControl;
    int rChan, gChan, bChan;

public:
    LED(uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t VCC = -1, bool negControl = 1, uint8_t rChan = 2, uint8_t gChan = 3, uint8_t bChan = 10);
    ~LED();
    void off();
    void rAnalog(uint8_t val);
    void gAnalog(uint8_t val);
    void bAnalog(uint8_t val);
};

#endif