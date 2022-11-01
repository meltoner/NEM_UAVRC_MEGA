/*
  Battery.h - Library for warping the functions controlling the Battery power levels
  Author - Konstantinos Papageorgiou kp at rei.gr 2022 
*/

#include "Arduino.h"
#include "Battery.h" 
#include "Context.h"

Battery::Battery(byte pin){}

void Battery::setup(Context &_context){
  context = &_context;
  apply();
}

void Battery::apply(){
  context->voltage =  analogRead(0) / 40.92; 
  // on latest state we read 8.26v insted of 7.5v
  // 15 12.6
  // 12 10.75
  // 10 9.65
  // 8 8.5
  // 7.5 8.35
  // 7.3 8.4 
  // 7.2 8.3
  // 7.1 8.20
  // 7   8.16
  // 6.9 8.13
  // 6.8 8.06
  // 6.7 8.01
  // 6.6 7.9- 8.11 
  //
// library(data.table)
// measurement <- data.table(
//   x = c( 8.5, 8.4, 8.3, 8.20, 8.16, 8.13, 8.06, 8.01, 7
//   y = c(  8,  7.3, 7.2, 7.1, 7, 6.9, 6.8, 6.7, 6.6)
// )
// fit <- lm(y~x, data = measurement)
// summary(fit)
// 
// adapt <- function(x)
//  -9.9030 + x * 2.0734
// 
// measurement[, Y := adapt(x)]
// x = sensor y = actual Y = predicted by the linear regression
//     x   y        Y
// 1: 8.50 8.0 7.720900
// 2: 8.40 7.3 7.513560
// 3: 8.30 7.2 7.306220
// 4: 8.20 7.1 7.098880
// 5: 8.16 7.0 7.015944
// 6: 8.13 6.9 6.953742
// 7: 8.06 6.8 6.808604
// 8: 8.01 6.7 6.704934
// 9: 7.90 6.6 6.476860

  context->voltage = -9.9030 + context->voltage * 2.0734;
  context->capacity = (byte)(context->voltage < 6 ? 0:( (context->voltage-7)/0.5 * 100));

  if(context->capacity > 100)
    context->capacity = 100;

  context->isLowBattery = context->voltage < 7.1;
}


// testing at 7.4 volt power supply
// 
// 1.1 watt at rest
// 4 wat wi servo activated
// 8.8 watt with lights only active
// 10 watt lights and servo 
// 6-15 watt mottors only
// 26 watt - full throtle, lights and servo
