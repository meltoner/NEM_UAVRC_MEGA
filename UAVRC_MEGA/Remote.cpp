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

void Remote::setup(Context &_context){
  context = &_context;
  IBus.begin(Serial);
  IBus.addSensor(IBUSS_RPM  );
  //IBus.addSensor(3);
  //IBus.addSensor(IBUSS_TEMP );
  delay(200);

  //Serial.println(F("IBUS ready."));
}

int Remote::readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue){ 
  uint16_t ch = IBus.readChannel(channelInput);
  if (ch < 100) 
    return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

void Remote::apply(){
  for(int i = 0; i < EXT_SENSORS; i++)
   context->ext_sensors[i] = (byte)readChannel(i, 0, 255, 0);
}

void Remote::telemetry(){
  IBus.setSensorMeasurement(IBUSS_RPM  ,5);  
  //IBus.setSensorMeasurement(3,5);  
  //IBus.setSensorMeasurement(2,600);
}
