/*
  Blink.h - Library for wraping the functions controling the Return to Blink 
  Created Konstantinos Papageorgiou  
*/

#include "Arduino.h"
#include "Blink.h" 
#include "Context.h"

Blink::Blink(byte pin){}

void Blink::setup(Context &_context){
  context = &_context;
  pinMode(47, OUTPUT);
  apply();
}

void Blink::apply(){
  digitalWrite(47, !digitalRead(47));
}
