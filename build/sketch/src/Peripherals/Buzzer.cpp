#include "Buzzer.h"

Buzzer::Buzzer(int pin, int VCC, int GND, int freq) : pin(pin), freq(freq)
{
  pinMode(pin, OUTPUT);

  if (GND != -1)
  {
    pinMode(GND, OUTPUT);
    digitalWrite(GND, LOW);
  }

  if (VCC != -1)
  {
    pinMode(VCC, OUTPUT);
    digitalWrite(VCC, HIGH);
  }
}

Buzzer::~Buzzer()
{
}

void Buzzer::buzz()
{
  if (lastUpdate == -1)
    lastUpdate = micros();

  if (micros() - lastUpdate >= 1e6 / freq / 2)
  {
    digitalWrite(pin, curStatus = 1 - curStatus);
    lastUpdate = micros();
  }
}

void Buzzer::buzzFor(int ms)
{
  int now = millis();
  while (millis() - now < ms)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(1e6 / freq / 2);
    digitalWrite(pin, LOW);
    delayMicroseconds(1e6 / freq / 2);
  }
}