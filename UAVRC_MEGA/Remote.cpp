/*
  Remote.h - Library for wraping the functions Remote control i/o
  Created Konstantinos Papageorgiou  
*/

#include "Arduino.h"
#include "Remote.h"
#include <IBusBM.h>

 
#define EXT_SENSORS 10

Remote::Remote(byte pin){
}


#define TEMPBASE 400    // base value for temperature is -40'C

uint16_t speed=0;
uint16_t temp=TEMPBASE+200; // start at 20'C

void Remote::setup(Context &_context){
  context = &_context;
  IBusServo.begin(Serial2); // digit 17
  IBusSensor.begin(Serial3); // digit 14

  IBusSensor.addSensor(1);//IBUSS_TEMP
  IBusSensor.addSensor(2);//IBUSS_RPM

  delay(200); 
}

int Remote::readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue){ 
  uint16_t ch = IBusServo.readChannel(channelInput);
  if (ch < 100) 
    return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void Remote::apply(){
  for(int i = 0; i < EXT_SENSORS; i++)
   context->ext_sensors[i] = (byte)readChannel(i, 0, 255, 0);
}

void Remote::telemetry(){
  IBusSensor.setSensorMeasurement(1, temp++);  // increase temperature by 0.1 'C every loop
  IBusSensor.setSensorMeasurement(2, context->targets[2]);  
}
