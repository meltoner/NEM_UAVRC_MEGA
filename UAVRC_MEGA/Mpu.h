/*
  Mpu.h - Library for wraping the functions controling the Mpunometer
  Author - Konstantinos Papageorgiou kp at rei.gr 2022  
*/
#ifndef Mpu_h
#define Mpu_h

#include "Arduino.h"
#include "Context.h"


class Mpu{
  public:
    Mpu(byte pin);
    void setup(Context &_context);
    void apply();
    void update();
  private:
    Context *context;
    byte _pin;
};

#endif
