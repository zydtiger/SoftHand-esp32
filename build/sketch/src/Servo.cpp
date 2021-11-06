#include "Servo.h"

Servo::Servo(SMS_STS *servoCtl, int id) : servoCtl(servoCtl), id(id), delayOffset(delayOffset)
{
}

Servo::~Servo()
{
}

void Servo::setCtl(SMS_STS *servoCtl)
{
    this->servoCtl = servoCtl;
}

void Servo::setId(int id)
{
    this->id = id;
}

void Servo::turnWithoutDelay(int degrees, double speedFactor)
{
    int targetPos = degrees * DEGTOPOS;
    int speed = speedFactor * MAX_SPEED;

    servoCtl->WritePosEx(id, targetPos, speed, 100);
    
    toDelay = (long)abs(targetPos-curPos) * 1000 / speed;

    curPos = targetPos;
}

void Servo::turn(int degrees, double speedFactor)
{
    turnWithoutDelay(degrees, speedFactor);
    delay(getDelay());
}

void Servo::update() {
    servoCtl->WritePosEx(id, curPos, MAX_SPEED, 100);
}

long Servo::getDelay()
{
    return toDelay;
}