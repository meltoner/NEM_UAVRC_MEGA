/*
  Hook.h - Library for wraping the functions controling Hook
  Author - Konstantinos Papageorgiou kp at rei.gr 2022 
*/

#ifndef Hook_h
#define Hook_h

#include "Arduino.h"
#include <Servo.h>
#include "Context.h"

class Hook{
  public:
    Hook(byte pin);
    void setup(Context &_context);
    void apply();
    void setHook(int value);

  private:
    byte _pin;
    boolean on = false;
    Servo hook;
    unsigned long applied = 0;
    Context *context;
};

#endif