/*
  Gps.h - Library for wraping the functions controling the Gps 
  Created Konstantinos Papageorgiou  
*/

#include "Arduino.h"
#include "Gps.h" 
#include <TinyGPS++.h>
#include "Context.h"

Gps::Gps(byte pin){}

void Gps::setup(Context &_context){
  context = &_context;
  Serial1.begin(9600);
}

void Gps::apply(){
  while (Serial1.available())
    gps.encode(Serial1.read());   

  context->latlng[0] = gps.location.lat();
  context->latlng[1] = gps.location.lng();
  
  context->isGPSLocked = context->latlng[0] != 0.0;
  
  if(context->isGPSLocked){
   context->intervals[5] = 1003;
   context->color = 1;
   processTarget();
  }

}

void Gps::processTarget(){ 
  context->targets[1] = gps.courseTo(context->latlng[0], context->latlng[1], context->TARGET_LAT, context->TARGET_LNG) ;  
  context->targets[2] = gps.distanceBetween(context->latlng[0], context->latlng[1], context->TARGET_LAT, context->TARGET_LNG) ;  
}