/*
  Mpu.h - Library for wraping the functions controling the Mpunometer
  Author - Konstantinos Papageorgiou kp at rei.gr 2022 
*/

#include "Arduino.h"
#include "Mpu.h"

#include <Wire.h>
#include "MPU6050_light.h"
#include "Context.h"

Mpu::Mpu(byte pin){  
  _pin = pin; 
}

MPU6050 sensor(Wire);

void Mpu::setup(Context &_context){
  context = &_context;

  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
  Wire.setWireTimeout(3000, true); //timeout value in uSec
  
  Serial.println(F("Begin mpu"));
  while(sensor.begin() != 0);
  
  Serial.println(F("Do not move"));
  delay(1000);
  sensor.calcOffsets(true, true);
  Serial.println(F("MPU ready."));

}

void Mpu::update(){
  sensor.update();
}

void Mpu::apply(){
    context->positional[0] = sensor.getAngleX(); 
    context->positional[1] = sensor.getAngleY();
    context->positional[2] = context->pruneDegrees(-sensor.getAngleZ());
}
