#ifndef _SERVO_H
#define _SERVO_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SCS/SCServo.h"

const double DEGTOPOS = 4095/360.;
const int MAX_SPEED = 3400;

class Servo
{
private:
    int curPos = 0;
    SMS_STS *servoCtl;
    int id;
    long toDelay = 0;
    int delayOffset;
public:
    Servo(SMS_STS *servoCtl = nullptr, int id = 1);
    ~Servo();
    void turn(int degrees, double speedFactor);
    void turnWithoutDelay(int degrees, double speedFactor);
    void setCtl(SMS_STS *servoCtl);
    void setId(int id);
    long getDelay();
    void update();
};


#endif