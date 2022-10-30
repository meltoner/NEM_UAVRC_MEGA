/*
  RGB.h - Library for wraping the functions controling the RGB led
  Author - Konstantinos Papageorgiou kp at rei.gr 2022
*/

#include "Arduino.h"
#include "RGB.h" 
#include "Context.h"

#define R_PIN 3
#define G_PIN 5
#define B_PIN 7

RGB::RGB(byte pin){}

void RGB::setup(Context &_context){
  context = &_context;
  pinMode(R_PIN, OUTPUT ); // green
  pinMode(G_PIN, OUTPUT ); // red
  pinMode(B_PIN, OUTPUT ); // blue
  apply();
}

void RGB::apply(){
  if(on)
    apply_color(context->color);
  else
    apply_color(7);
  
  on = !on;
}

void RGB::apply_color(byte color){
  set_color(R[color], G[color], B[color]);
}

void RGB::set_color(int red_value, int green_value, int blue_value){
  analogWrite(R_PIN, red_value);
  analogWrite(G_PIN, green_value);
  analogWrite(B_PIN, blue_value);
}