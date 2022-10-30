/*
  Relay.h - Library for wraping the functions controling the Relay 
  Author - Konstantinos Papageorgiou kp at rei.gr 2022
*/

#ifndef Relay_h
#define Relay_h

#include "Arduino.h" 
#include "Context.h"

class Relay{
  public:
    Relay(byte pin, byte position);
    void setup(Context &_context);
    void apply();
  private:
    Context *context;
    byte port;
    byte index;
};

#endif