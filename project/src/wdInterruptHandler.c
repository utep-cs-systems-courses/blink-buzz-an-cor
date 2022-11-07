#include <msp430.h>
#include "buttons.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"

void __interrupt_vec(WDT_VECTOR) WDT(){

  static char blink_count = 0;
  if(++blink_count == 63){ //Every fourth of a second
    if(turnoff_on) { //if switch 4 is pressed, call turnoff();
      turnoff();
    }
    else if(siren_on) { //if switch 1 is pressed call siren();
        siren();
    }
    blink_count = 0;
  }
}
