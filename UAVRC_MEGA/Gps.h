/*
  Gps.h - Library for wraping the functions controling the Gpsnometer
  Created Konstantinos Papageorgiou  
*/

#ifndef Gps_h
#define Gps_h

#include "Arduino.h" 
#include <TinyGPS++.h>
#include "Context.h"

class Gps{
  public:
    Gps(byte pin);
    void setup(Context &_context);
    void apply();
    void processTarget();    

  private:
    Context *context;
    TinyGPSPlus gps;
};

#endif