#include "ServoCtl.h"

ServoCtl::ServoCtl(int servoCnt, HardwareSerial *serial) : servoCnt(servoCnt)
{
    servoCtl.pSerial = serial;

    servos = new Servo[servoCnt + 1];
    for (int i = 1; i <= servoCnt; i++)
    {
        servos[i].setCtl(&servoCtl);
        servos[i].setId(i);
    }
}

ServoCtl::~ServoCtl()
{
    delete servos;
}

void ServoCtl::update()
{
    for (int i = 1; i <= servoCnt; i++)
        servos[i].update();
}

void ServoCtl::turnId(int id, int degrees, double speedFactor)
{
    servos[id].turn(degrees, speedFactor);
}

void ServoCtl::resetId(int id, double speedFactor)
{
    turnId(id, 0, speedFactor);
}

void ServoCtl::turn(int degrees, double speedFactor)
{
    // this->servo.WritePosEx(1, 4095, 3400, 50); //舵机(ID1)以最高速度V=3400步/秒，加速度A=50(50*100步/秒^2)，运行至P1=4095位置

    for (int i = 1; i <= servoCnt; i++)
        servos[i].turnWithoutDelay(degrees, speedFactor);

    long maxToDelay = 0;
    for (int i = 1; i <= servoCnt; i++)
        maxToDelay = max(maxToDelay, servos[i].getDelay());
    delay(maxToDelay);
}

void ServoCtl::reset(double speedFactor)
{
    for (int i = 1; i < servoCnt; i++)
        servos[i].turnWithoutDelay(0, speedFactor);

    servos[5].turnWithoutDelay(100, speedFactor);

    long maxToDelay = 0;
    for (int i = 1; i <= servoCnt; i++)
        maxToDelay = max(maxToDelay, servos[i].getDelay());
    delay(maxToDelay);
}