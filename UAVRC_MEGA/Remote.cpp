/*
  Remote.h - Library for wraping the functions Remote control i/o
  Author - Konstantinos Papageorgiou kp at rei.gr 2022
*/

#include "Arduino.h"
#include "Remote.h"
#include <IBusBM.h>

 
#define EXT_SENSORS 10

Remote::Remote(byte pin){
}

void Remote::setup(Context &_context){
  context = &_context;
  IBusServo.begin(Serial2);  // digit 17
  IBusSensor.begin(Serial3); // digit 14

  IBusSensor.addSensor(0x00); // Voltage sensor // shown as IntV2
  IBusSensor.addSensor(0x02); // GPS distance from home
  //IBusSensor.addSensor(0x14); // GPS degrees from home 
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
  IBusSensor.setSensorMeasurement(1, context->voltage * 100);
  IBusSensor.setSensorMeasurement(2, context->targets[2]);
  //IBusSensor.setSensorMeasurement(3, (uint16_t)abs(context->targets[1]));
}
