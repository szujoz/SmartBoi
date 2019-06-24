#include "led.h"
#include <Arduino.h>

LED::LED(int Pin)
{
  pin = Pin;
  state = eLED_OFF;
}

void LED::init(void)
{
  pinMode(pin, OUTPUT);
  turnON();
}

int LED::getPin(void)
{
  return pin;
}

void LED::turnON(void)
{
  state = eLED_ON;
  digitalWrite(pin, HIGH);
}

void LED::turnOFF(void)
{
  state = eLED_OFF;
  digitalWrite(pin, LOW);
}

void LED::toggle(void)
{
  if (state == eLED_ON)
  {
    state = eLED_OFF;
    digitalWrite(pin, LOW);
  }
  else
  {
    state = eLED_ON;
    digitalWrite(pin, HIGH);
  }
}
