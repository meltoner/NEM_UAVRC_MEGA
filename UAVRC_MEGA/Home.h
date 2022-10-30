/*
  Home.h - Library for wraping the functions controling the Homenometer
  Author - Konstantinos Papageorgiou kp at rei.gr 2022
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
    int distance[5] = {20, 15, 8, 4, 0};
    int onTime[5] = {6000, 2000, 1500, 1400, 1000};
    int offTime[5] = {2500, 3000, 4000, 5000, 1000};
    float speedWeight[5] = {1, 0.9, 0.7, 0.7, 0};
    Context *context;
};

#endif