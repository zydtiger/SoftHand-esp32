#ifndef _HAND_H
#define _HAND_H

#include "ServoCtl.h"
#include "Peripherals/BreathingLED.h"
#include "Peripherals/Buzzer.h"

class Hand
{
private:
    ServoCtl *fingerCtl, *wristCtl;
    BreathingLED *ledIndicator;
    Buzzer *buzzer;

public:
    const int FULL_TURN = 30;
    const int FINGER_DEG_TO_SERVO_DEG = 10; // this should change according to the experiment

    Hand(HardwareSerial *serial, BreathingLED *ledIndicator = nullptr, Buzzer *buzzer = nullptr);
    ~Hand();
    void turnFinger(int finger, int percent);
    void turnFingerDeg(int finger, int deg);
    void contract(uint16_t turn);
    void fingerReset();
    void indicatorOn();
    void update(); //responsible for sending a continuous signal to the servos to keep the cur status
};

#endif