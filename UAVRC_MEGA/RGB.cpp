/*
  RGB.h - Library for wraping the functions controling the RGB led
  Author - Konstantinos Papageorgiou kp at rei.gr 2022
*/

#include "Arduino.h"
#include "RGB.h" 
#include "Context.h"

RGB::RGB(byte pin){}

void RGB::setup(Context &_context){
  context = &_context;
  pinMode(44, OUTPUT); // green
  pinMode(45, OUTPUT); // red
  pinMode(46, OUTPUT);  // blue
  apply();
}

void RGB::apply(){
  analogWrite(45, R[context->color]);
  analogWrite(44, G[context->color]);
  analogWrite(46, B[context->color]);
}
