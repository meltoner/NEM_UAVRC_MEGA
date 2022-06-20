// Konstantinos Papageorgiou - 2022 - kp@rei.gr
// ss
#include "Context.h"
#include "Invoker.h"

#include "Remote.h"
#include "Blink.h"

#include <EEPROM.h>

Context context(0);
Invoker invoker(0);

Remote remote(0);
Blink blink(0);

//-----------------------------------------

void setup() {
  context.setup();
  blink.setup(context);
  remote.setup(context);
  invoker.setup(context);
}

void apply_very_fast_invoker(){

}

void apply_fast_invoker(){
  remote.apply();
}

void apply_invoker(){

}

void apply_slow_invoker(){
  context.apply(); // every 0.5 second printout / log enviromental variables
  remote.telemetry(); 
}

void heartBeat(){
  //dynamic periodicity 
  // Every : 3s when no gps, 1sec when gps lock, 0.5 seconds when returing to home is active, 0.1 second when power is less than 30%.
  blink.apply();
}

void apply_slower_invoker(){
}

void updateMagOffset(){
}

void run_invoker(int i){
    switch(i){
      case 0: apply_very_fast_invoker(); break;
      case 1: apply_fast_invoker(); break;
      case 2: apply_invoker(); break;
      case 3: apply_slow_invoker(); break;
      case 4: apply_slower_invoker(); break;
      case 5: heartBeat(); break;
      case 6: updateMagOffset();break;
      case 7: //home.bursts();
            break;
      case 100: break;
    }
}

void loop(){
  int actionIndex = invoker.apply();
  while(actionIndex != 100){
    run_invoker(actionIndex);
    actionIndex = invoker.apply();
  }
}
