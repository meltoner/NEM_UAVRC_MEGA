/*
  Remote.h - Library for wraping the functions controling the remote control i/o
  Author - Konstantinos Papageorgiou kp at rei.gr 2022 
*/

#ifndef Remote_h
#define Remote_h

#include "Arduino.h"
#include <IBusBM.h>
#include "Context.h"

class Remote{
  public:
    Remote(byte pin);
    void setup(Context &_context);
    void apply();
    int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue);
    void telemetry();
    Context *context;
  private:
    IBusBM IBusServo;
    IBusBM IBusSensor;
};

#endif