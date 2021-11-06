#include "Hand.h"

Hand::Hand(HardwareSerial *serial, BreathingLED *ledIndicator, Buzzer *buzzer)
    : ledIndicator(ledIndicator), buzzer(buzzer)
{
    fingerCtl = new ServoCtl(5, serial);
    fingerCtl->reset();
}

Hand::~Hand()
{
}

void Hand::update() {
    fingerCtl->update();
}

void Hand::indicatorOn()
{
    if (ledIndicator)
    {
        ledIndicator->getRawLED()->off();
        ledIndicator->getRawLED()->rAnalog(255);
    }

    if (buzzer)
        buzzer->buzzFor(100);
}

void Hand::turnFinger(int finger, int percent)
{
    indicatorOn();
    fingerCtl->turnId(finger, (long)percent * FULL_TURN * FINGER_DEG_TO_SERVO_DEG / 100);
}

void Hand::turnFingerDeg(int finger, int deg) {
    indicatorOn();
    fingerCtl->turnId(finger, deg*2);
}

void Hand::contract(uint16_t turn)
{
    indicatorOn();
    // fingerReset();
    delay(200);
    fingerCtl->turn(turn * FINGER_DEG_TO_SERVO_DEG, 0.5);
}

void Hand::fingerReset()
{
    indicatorOn();
    fingerCtl->reset();
}