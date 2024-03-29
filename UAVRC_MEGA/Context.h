/*
  Context.h - Library for wraping the functions controling the Context / enviroment information
  Author - Konstantinos Papageorgiou kp at rei.gr 2022  
*/

#ifndef Context_h
#define Context_h

#include "Arduino.h" 

class Context{
  public:
    Context(byte pin);
    void setup();
    void apply();
    void reflectSensor(float value, byte precission);
    int transferFunction(int value, int theshold, int add, int divider);
    
    int pruneDegrees(float value);

    boolean isSwitchA();
    boolean isSwitchB();
    boolean isSwitchCHalf();
    boolean isSwitchC();
    boolean isSwitchD();

    void setGPSTarget(double LAT, double LNG);

    // Enviroment values
    //-----------------------
    // GPS related
    boolean isGPSLocked = false;
    unsigned long GPSLockTime = 0;

    double latlng[2] = {11.111111, 11.112222}; // gps position
    double latlngPast[2] = {-400, -400}; // gps position
    boolean isStationary = false;

    double TARGET_LAT = 37.9584512; // Pagkrati
    double TARGET_LNG = 23.7502464;
    int satellites = 0;
    double speed = 0;

    byte toHomeSpeed = 50;
    float toHomeSpeedWeight = 1;
    byte steer_center = 86;
    
    boolean toHomeSet = false;
    boolean toHomeWait = false;
    boolean toHomeActive = false;

    // Positional related values
    float positional[4] = {0, 0, 0, 0}; // x, y, z, magz
    float derivatives[3] = {0, 0, 0}; // offset, headings,target heading diff
    float targets[5] = {0, 0, 0, 0, 0}; // heading target, target gps degree, target gps distance meters, x distance, y distance

    // Remote controler
    byte ext_sensors[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // flysky gradient, switches

    // Power related
    float voltage = 0;
    byte capacity = 100;

    boolean isLowBattery = false;

    // Server and motor values
    byte actuators[3] = {0, 0, 0}; // servo, speed, hook
    byte color = 1;
    
    // Invoker variables - execution functions frequencies
    int intervals[8] = {10, 52, 104, 506, 1008, 1010, 10000, 3000};
    unsigned long now = millis();
    unsigned long timers[8] = {now, now, now, now, now, now, now};

    boolean relays[2] = {false, false};
  private:
    byte _pin;
};

#endif