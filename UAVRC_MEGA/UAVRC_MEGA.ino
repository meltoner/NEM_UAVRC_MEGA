//
// @author : Konstantinos L. Papageorgiou - 2022 - kp at rei.gr
// @repo: https://github.com/meltoner/NEM_UAVRC_MEGA
//
// # NEM UAVRC MEGA
// 
// NEM Unmanned Vehicle Remote Controlled software on Arduino Mega 2550 pro
//

#include "Context.h"
#include "Invoker.h"

#include "Mag.h"
#include "Gps.h" 
#include "Mpu.h" 
#include "Steer.h"
#include "hook.h"
#include "Throttle.h"
#include "Remote.h"
#include "Telemetry.h"
#include "Home.h"
#include "RGB.h"
#include "Battery.h"
#include "Relay.h"

Context context(0);
Invoker invoker(0);

Mag mag(0);
Gps gps(0);
Mpu mpu(0);

Throttle throttle(2);
Steer steer(4);
Hook hook(6);

Remote remote(0);
Telemetry telemetry(0);

Home home(0);
RGB rgb(0);
Battery battery(0);

Relay relayA(50, 0);
Relay relayB(52, 1);

//-----------------------------------------

void setup() {
  context.setup();  
  rgb.setup(context);
  throttle.setup(context);      rgb.apply_color(0);  delay(100);
  remote.setup(context);        rgb.apply_color(1);  delay(500);
  delay(2000);
  mpu.setup(context);           rgb.apply_color(2);  delay(500);
  mag.setup(context);           rgb.apply_color(3);  delay(500);
  hook.setup(context);          
  gps.setup(context);           rgb.apply_color(5);  delay(500);
  steer.setup(context);         rgb.apply_color(4);  delay(200);
  battery.setup(context);       rgb.apply_color(6);  delay(500);
  home.setup(context);
  invoker.setup(context);
  relayA.setup(context);
  relayB.setup(context);        context.color = 3;  delay(500);
  telemetry.setup(context);

}

//-----------------------------------------

void apply_interval_0(){
  mag.apply();
  telemetry.apply();
  mpu.apply();
}

void apply_interval_1(){
  remote.apply();
  steer.apply();
  throttle.apply();
}

void apply_interval_2(){
  gps.apply();
  telemetry.run();
  home.apply();
  rgb.apply();
  telemetry.run();
  relayA.apply();
  relayB.apply();  
}

void apply_interval_3(){
  context.apply();
  hook.apply();
}

void apply_interval_4(){
}

void apply_interval_5(){
  battery.apply();
}

void apply_interval_6(){
  if(context.toHomeActive)
    mag.updateMagOffset();

  gps.testStationary();
}

void apply_interval_7(){
  home.bursts();
}


//-----------------------------------------

void run_invoker(int i){
    switch(i){
      case 0: apply_interval_0(); break;
      case 1: apply_interval_1(); break;
      case 2: apply_interval_2(); break;
      case 3: apply_interval_3(); break;
      case 4: apply_interval_4(); break;
      case 5: apply_interval_5(); break;
      case 6: apply_interval_6();break;
      case 7: apply_interval_7();break;
      case 100: break;
    }
}

//-----------------------------------------

void loop(){
  mpu.update();
  telemetry.run();
  int actionIndex = invoker.apply();
  while(actionIndex != 100){
    run_invoker(actionIndex);
    telemetry.run();
    actionIndex = invoker.apply();
  } 
}
