/*
  Throttle.cpp - Library for wraping the functions controling the Throttle
  Created Konstantinos Papageorgiou  
*/

#include "Arduino.h"
#include "Throttle.h"
#include <Servo.h>
#include "Context.h"

Throttle::Throttle(byte pin){  
  _pin = pin;
}

void Throttle::setup(Context &_context){
  context = &_context;
  throttle.attach(_pin); 
  throttle.writeMicroseconds(900); // send "stop" signal to ESC. Also necessary to arm the ESC.
  delay(1000); // delay to allow the ESC to recognize the stopped signal.
}

void Throttle::apply(){
  if(context->toHomeActive)    
    setThrottle( (int)( (float)context->toHomeSpeed * context->toHomeSpeedWeight), 50);    
  else
    setThrottle(context->transferFunction(context->ext_sensors[2], 15, 20, 300), context->ext_sensors[4]);
}

void Throttle::setThrottle(int value, int limiter){
  if(value > limiter)
    value = limiter;

  //lower the throttle when turning
  int steerResistance = abs(context->actuators[0]-context->steer_center) ;

  if(value > 25 && steerResistance > 15 )
    value = (int)(value * 0.75);

  if(context->actuators[1] != value){
    // Incremental acceleration when that is large
    if(value - context->actuators[1] > 45)
      value = context->actuators[1] * 0.95 + value * 0.05;

    context->actuators[1] = value;

    //compensate for streer

    int pwmVal = map(value, 0, 255, 1000, 2000); // maps to PWM value.
    throttle.writeMicroseconds(pwmVal); // Send signal to ESC.  
  }  
}
