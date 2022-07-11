/*
  Home.h - Library for wraping the functions controling the Return to Home 
  Created Konstantinos Papageorgiou  
*/

#include "Arduino.h"
#include "Home.h" 
#include "Context.h" 

Home::Home(int pin){}

void Home::setup(Context &_context){
  context = &_context;
}

void Home::apply(){
  // Update return to home gps target
  if( context->isSwitchB() && context->isGPSLocked ){    
    context->setGPSTarget( context->latlng[0], context->latlng[1]);
    context->targets[0] = context->targets[1];
  }

  context->toHomeActive = context->isSwitchA() && context->isSwitchD() && context->isGPSLocked;
  
  // Derive target heading and speed from gps target
  if(context->toHomeActive){
    context->color = 2;
    context->targets[0] = context->targets[1];

    for(int i = 0 ;i < 5;i++){
      if(context->targets[2] > distance[i]){
        context->toHomeSpeedWeight = speedWeight[i];

        if(context->toHomeWait){
          context->toHomeSpeedWeight = 0;
          context->intervals[7] = offTime[i];
        }else{
          context->intervals[7] = onTime[i];
        }

        break;
      }
    }

  }

}

void Home::bursts(){
  context->toHomeWait = !context->toHomeWait;
}