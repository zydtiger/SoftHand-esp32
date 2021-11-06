#include "LED.h"

/*
 * LEDC Chan to Group/Channel/Timer Mapping
** ledc: 0  => Group: 0, Channel: 0, Timer: 0
** ledc: 1  => Group: 0, Channel: 1, Timer: 0
** ledc: 2  => Group: 0, Channel: 2, Timer: 1
** ledc: 3  => Group: 0, Channel: 3, Timer: 1
** ledc: 4  => Group: 0, Channel: 4, Timer: 2
** ledc: 5  => Group: 0, Channel: 5, Timer: 2
** ledc: 6  => Group: 0, Channel: 6, Timer: 3
** ledc: 7  => Group: 0, Channel: 7, Timer: 3
** ledc: 8  => Group: 1, Channel: 0, Timer: 0
** ledc: 9  => Group: 1, Channel: 1, Timer: 0
** ledc: 10 => Group: 1, Channel: 2, Timer: 1
** ledc: 11 => Group: 1, Channel: 3, Timer: 1
** ledc: 12 => Group: 1, Channel: 4, Timer: 2
** ledc: 13 => Group: 1, Channel: 5, Timer: 2
** ledc: 14 => Group: 1, Channel: 6, Timer: 3
** ledc: 15 => Group: 1, Channel: 7, Timer: 3
*/

LED::LED(uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t VCC, bool negControl, uint8_t rChan, uint8_t gChan, uint8_t bChan)
    : negControl(negControl), rChan(rChan), gChan(gChan), bChan(bChan)
{
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);

    ledcSetup(rChan, 50, 8);
    ledcSetup(gChan, 50, 8);
    ledcSetup(bChan, 50, 8);

    ledcAttachPin(rPin, rChan);
    ledcAttachPin(gPin, gChan);
    ledcAttachPin(bPin, bChan);

    off();

    if (VCC != -1)
    {
        pinMode(VCC, OUTPUT);
        digitalWrite(VCC, HIGH);
    }
}

LED::~LED()
{
}

void LED::off()
{
    rAnalog(0);
    bAnalog(0);
    gAnalog(0);
}

void LED::rAnalog(uint8_t val)
{
    ledcWrite(rChan, negControl ? 255 - val : val);
}
void LED::gAnalog(uint8_t val)
{
    ledcWrite(gChan, negControl ? 255 - val : val);
}
void LED::bAnalog(uint8_t val)
{
    ledcWrite(bChan, negControl ? 255 - val : val);
}