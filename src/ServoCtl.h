#ifndef _SERVOCTL_H
#define _SERVOCTL_H

#include "Servo.h"

class ServoCtl
{
private:
    SMS_STS servoCtl;
    int servoCnt;
    Servo *servos;
public:
    ServoCtl(int servoCnt = 0, HardwareSerial *serial = nullptr);
    ~ServoCtl();
    void turnId(int id, int degrees, double speedFactor = 1);
    void resetId(int id, double speedFactor = 1);
    void turn(int degrees, double speedFactor = 1);
    void reset(double speedFactor = 1);
    void update();
};

#endif
