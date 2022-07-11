/*
  Home.h - Library for wraping the functions controling the Homenometer
  Created Konstantinos Papageorgiou  
*/

#ifndef Home_h
#define Home_h

#include "Arduino.h" 
#include "Context.h"

class Home{
  public:
    Home(int pin);
    void setup(Context &_context);
    void apply();
    void bursts();
  private:
    int distance[5] = {20, 12, 8, 4, 2};
    int onTime[5] = {6000, 3000, 2000, 1000, 1000};
    int offTime[5] = {2000, 3000, 4000, 5000, 1000};
    float speedWeight[5] = {1, 0.9, 0.7, 0.6, 0};

    Context *context;
};

#endif