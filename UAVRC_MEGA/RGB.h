/*
  Blink.h - Library for wraping the functions controling the Blink 
  Author - Konstantinos Papageorgiou kp at rei.gr 2022
*/

#ifndef RGB_h
#define RGB_h

#include "Arduino.h" 
#include "Context.h"

class RGB{
  public:
    RGB(byte pin);
    void setup(Context &_context);
    void apply();
    void apply_color(byte color);
    void set_color(int red_value, int green_value, int blue_value);
  private:
    boolean on = true;
    //          red   green blue    yellow  cyan    purple  tirquaz closed
    int R[8] = {0,    255,  255,    0,      255,    60,     255,    255};
    int G[8] = {255,  0,    255,    60,     60,     255,    0,      255};
    int B[8] = {255,  255,  0,      255,    0,      0,      0,      255};

    Context *context;
};

#endif