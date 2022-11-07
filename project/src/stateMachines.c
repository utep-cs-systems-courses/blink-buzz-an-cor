#include <msp430.h>
#include "buttons.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"

unsigned char siren_on = 0;
unsigned char turnoff_on = 0;

void selectFunction()
{
  //If button 4 is pressed,all leds and the buzzer is turned off
  if(sw4_state_down){
    siren_on = 0;
    turnoff_on = 1;
    
  }
  //If button 1 is pressed a siren occurs
  if(sw1_state_down){
    siren_on = 1;
    turnoff_on = 0;
  }
}

 
// Uses switch 4 (P2.3) to turnoff all leds and the buzzer
void turnoff()

{
  turn_green_off();
  turn_red_off();
  turn_buzzer_off();
  led_changed = 1;
  led_update();

}

//continousl sirens down until period is 100, then starts over
void siren()
{
  static int period = 1000; //initial period
  static char siren_state = 0;//holds siren state
  
  switch (siren_state) {
  case 0:
    //if period is 100, resets period to 1000
    if(period == 100){
      period = 1000;
    }
 
    right();// turns red on, green off 
    buzzer_set_period(period);//sets buzzer with current period
    period = period - 100;//decreases
    siren_state = 1;//go to state 1
    break;
  case 1:
    //if period is 100, resets period to 1000
    if(period == 100){
      period = 1000;
    }
 
    left(); //turns green on, red off
    buzzer_set_period(period);//sets buzzer with current period
    period = period - 100; //decreases period
    siren_state = 0;//goes to state 0
    break;
  }
  //updates leds
  led_changed = 1;
  led_update();
}
