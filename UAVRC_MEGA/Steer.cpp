/*
  Steer.h - Library for wraping the functions controling the Steer
  Author - Konstantinos Papageorgiou kp at rei.gr 2022  
*/

#include "Arduino.h"
#include "Steer.h"
#include <Servo.h>
#include "Context.h"

Steer::Steer(byte pin){  
  _pin = pin;
}

void Steer::setup(Context &_context){
  context = &_context;
  steer.attach(_pin);
  on = true;
  setSteer(context->steer_center);
}

int Steer::getHeadingDifference(){

  if(context->derivatives[2] > 30)
   return 30;

  if(context->derivatives[2] < -30)
   return -30;

  return (int)(context->derivatives[2] * (abs(context->derivatives[2])/30) );
}

void Steer::setSteer(int value){
  if(context->actuators[0] != value){
    applied = context->now;
    steer.write(context->actuators[0] = value);  
  }
}

void Steer::apply(){
  // steering angle derivation
  int sensorValue = map(context->ext_sensors[0], 0, 255, -30, 30);
  
  sensorValue = context->transferFunction(sensorValue, 3, 6, 30);

  int value = context->steer_center - sensorValue;
 

  if(abs(sensorValue) < 5)
    value = context->steer_center - getHeadingDifference();
  else
    context->targets[0] = context->derivatives[1] + sensorValue * 1.2;

  // save power when reached context->steer_center
  if( context->actuators[0] == value ){
    if(on && (context->now - applied) > 4000 ){    
      steer.detach();
      on = false;      
    }
  }else{
    if(!on){
      steer.attach( _pin );
      on = true;
    }
  }

  if(on)setSteer( value );

}
