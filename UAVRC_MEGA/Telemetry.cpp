/*
  Telemetry.h - Library for wraping the functions Telemetry control i/o
  Author - Konstantinos Papageorgiou kp at rei.gr 2022
  
*/

#include "Arduino.h"
#include "Telemetry.h"

Telemetry::Telemetry(byte pin){}

void Telemetry::setup(Context &_context){
  context = &_context;
  telem.begin();

  telem.addSensor(IBUS_MEAS_TYPE_GPS_DIST); // distance from home
  //telem.addSensor(0x0a); // satelites

  telem.addSensor(0x0c);// lat 1st
  telem.addSensor(IBUS_MEAS_TYPE_ARMED); // lat 2nd
  telem.addSensor(IBUS_MEAS_TYPE_FLIGHT_MODE); // lon 1st
  telem.addSensor(0x0e); // lon 2nd
  telem.addSensor(0x03); //external voltage

  //telem.addSensor(IBUS_MEAS_TYPE_SPE); // speed m/s
}

void Telemetry::run(){
  telem.run();
}

String Telemetry::double2string(double n, int ndec) {
  String r = "";
  int v = n;
  r += v;     // whole number part
  //r += '.';   // decimal point
  int i;
  for (i=0;i<ndec;i++) {
      // iterate through each decimal digit for 0..ndec 
      n -= v;
      n *= 10; 
      v = n;
      r += v;
  }
  return r;
}

int stringPartInt(String in, int from, int to) {
    String r = "";
    for (int i=from;i<to;i++) 
        r += in[i];
    return  r.toInt();
}

void Telemetry::apply(){

  telem.setSensorValue(1, context->targets[2]);   // distance from home
  //telem.setSensorValue(3, context->satellites );  // gps sattelites
 
  //lat
  String toStringValue = double2string(context->latlng[0], 6);
  telem.setSensorValue(2, stringPartInt(toStringValue, 0, 4) );  
  telem.setSensorValue(3, stringPartInt(toStringValue, 4, 8) );  
  telem.run(); 
  //lon
  toStringValue = double2string(context->latlng[1], 6);
  telem.setSensorValue(4, stringPartInt(toStringValue, 0, 4) );  
  telem.setSensorValue(5, stringPartInt(toStringValue, 4, 8) );
  telem.setSensorValueFP(6, context->voltage);    // external voltage

  //telem.setSensorValue(8, context->speed * 100); // visible as speed
  telem.run(); 
}

// Note on IBUSTelemetry - have lowered the microseconds delay to 10 insteand of 100
// https://github.com/qba667/FlySkyI6/blob/master/source/source/ibustelemetry.h
// https://www.cloudacm.com/?p=3865

