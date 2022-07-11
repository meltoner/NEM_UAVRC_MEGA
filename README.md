# NEM UAVRC MEGA

NEM Unmanned Vehicle Remote Controlled software on Arduino Mega 2550 pro

## Software Features :

- Software utilises an MPU6050, GPS, Servo, ESC, magnetometer and an amphidromous remote control, powered by an arduino mega pro.
- Sensors and accuators are all in classes
- Impeleent seven tasks execution frequencies
- Adaptive steering based on target degrees
- Boots esc motor, and applies a non liner transfer function to the speed remote input
- Computes degrees heading at boot time, used as an offcet for the mpu degree heading
- Derives distance and degrees from a target gps LAT LOT
- Return to target gps / home on signal loss or switch D
- Adaptive speed while approaching target
- Detection of low battery and return to home
- Transmits distance of vehicle from target gps
- Lowers throttle while turning
- RGB Led indicator - no gps red, gps lock - green, return to home blue
- Variable led blinking indicator
- Target gps restoration, after power loss

## Hardware

Sensors :

- Gps : Ublox M8N with compass
- Magmetometer : M8n's HMC5883
- Receiver : flysky F9-ia10b
- MPU : MPU6050
- Voltage sensor 0-25v MH-electronic

Main components : 
- Transmitter : flysky FS-I6X
- Receiver : [flysky FS-1A10B](https://www.flysky-cn.com/ia10b-canshu)
- Arduino mega pro 2560 

Other: 

- 10mm LED Green and Red
- RGB LED
- 3 Pin Female connectors, ribbon cable, conectors, 3d mount board, box, battery, etc
