# NEM_UAVRC_MEGA

NEM Unmanned Vehicle Remote Controlled software on Arduino Mega 2550 pro

## Software Features :

- Software utilises an MPU, GPS, Servo, ESC, magnetometer and an amphidromous remote control, powered by an arduino mega pro.
- Sensors and accuators are all in classes
- Considers seven interval / frequencies of task execution
- Controls steering based on target 
- Boots esc motor, and applies a non liner transfer function to the speed remote input
- Computes degrees heading at boot time, used as an offcet for the mpu degree heading
- Derives distance and degree from a target gps LAT LOT
- Return to home on signal loss
- Detection of low battery and return to home
- Transmits distance of vehicle from Home

## Hardware

Sensors :

- Gps : M8n
- Magmetometer : M8n's HMC5883
- Receiver : flysky F9-ia10b
- MPU : MPU6050
- Voltage sensor 0-25v MH-electronic

Main components : 
- Transmitter : flysky FS-I6X
- Receiver : flysky FS-1a10b
- Arduino mega pro 2560 

Other: 

- 10mm LED Green and Red
- RGB LED
- 3 Pin Female connectors, ribbon cable, conectors, 3d mount board, box, battery, etc
