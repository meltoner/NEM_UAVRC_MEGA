/*
  Hook.h - Library for wraping the functions controling the Hook servo
  Author - Konstantinos Papageorgiou kp at rei.gr 2022  
*/

#include "Arduino.h"
#include "Hook.h"
#include <Servo.h>
#include "Context.h"

Hook::Hook(byte pin){  
  _pin = pin;
}

void Hook::setup(Context &_context){
  context = &_context;
  hook.attach(_pin);
  on = true;
  setHook(0);
}

void Hook::setHook(int value){
  if(context->actuators[2] != value){
    applied = context->now;
    hook.write(context->actuators[2] = value);  
  }
}

void Hook::apply(){
  int sensorValue = context->ext_sensors[7];
  // save power when reached context->hook_center
  if(context->actuators[2] == sensorValue ){
    if(on && (context->now - applied) > 1000  ){    
      hook.detach();
      on = false;      
    }
  }else{
    if(!on){
      hook.attach(_pin);
      on = true;
    }
  }

  if(on)
    setHook( sensorValue );

}
