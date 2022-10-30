/*
  Gps.h - Library for wraping the functions controling the Gps 
  Author - Konstantinos Papageorgiou kp at rei.gr 2022 
*/

#include "Arduino.h"
#include "Gps.h" 
#include <TinyGPS++.h>
#include "Context.h"

Gps::Gps(byte pin){}
//https://content.u-blox.com/sites/default/files/products/documents/u-blox8-M8_ReceiverDescrProtSpec_UBX-13003221.pdf

void Gps::setup(Context &_context){
  Serial.print("setup");
  context = &_context;
  Serial1.begin(9600);
}

void Gps::apply(){
  boolean isAvailable = false;
  while (Serial1.available() > 0){
    isAvailable = true;
    gps.encode(Serial1.read());   
  }

  if(isAvailable && gps.location.isValid()){

    context->latlng[0] = gps.location.lat();
    context->latlng[1] = gps.location.lng();
    
    context->satellites = gps.satellites.value();
    //context->speed = gps.speed.mps();
    context->isGPSLocked = context->latlng[0] != 0.0 || context->latlng[0] != 11.1111;

    if(context->isGPSLocked){
      context->color = 1; // green gps is locked
      if(context->GPSLockTime == 0){
        context->GPSLockTime = context->now;        
      }else{
        if(!context->toHomeSet && context->isStationary){
          context->toHomeSet = true;
          context->TARGET_LAT = context->latlng[0];
          context->TARGET_LNG = context->latlng[1];          
        }
      }
      if(context->toHomeSet)
        context->color = 2; // blue

      processTarget();
    }
  }else{
    context->color = 3; // yellow
    context->isGPSLocked = false;
  }

  context->color = context->isLowBattery?0:context->color;

}

void Gps::testStationary(){
  if(!context->isStationary && context->isGPSLocked){
    if(context->latlngPast[0] != -400)
      if(((abs(context->latlng[0] - context->latlngPast[0]) + abs(context->latlng[1] - context->latlngPast[1]) ) * 100000) < 3)
        context->isStationary = true;
    context->latlngPast[0] = context->latlng[0];
    context->latlngPast[1] = context->latlng[1];
  }
}

void Gps::processTarget(){ 
  context->targets[1] = gps.courseTo(
    context->latlng[0], context->latlng[1], 
    context->TARGET_LAT, context->TARGET_LNG
  );  
  context->targets[2] = gps.distanceBetween(
    context->latlng[0], context->latlng[1], 
    context->TARGET_LAT, context->TARGET_LNG
  );
}