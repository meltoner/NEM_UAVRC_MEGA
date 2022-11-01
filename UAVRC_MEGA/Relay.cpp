/*
  Relay.h - Library for wraping the functions controling the Relay 
  Author - Konstantinos Papageorgiou kp at rei.gr 2022
*/

#include "Arduino.h"
#include "Relay.h" 
#include "Context.h"

Relay::Relay(byte pin, byte position){
  port = pin;
  index = position;
}

void Relay::setup(Context &_context){
  context = &_context;
  pinMode(port, OUTPUT);
  digitalWrite(port, HIGH);
  delay(200);
  apply();
}

void Relay::toggle(){
  state = !state;
}

void Relay::apply(){
  if(!context->isLowBattery){
    digitalWrite(port, context->isSwitchA());
  }else{
    digitalWrite(port, state);
  }
}
