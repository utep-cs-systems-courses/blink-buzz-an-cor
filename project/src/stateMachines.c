#include <msp430.h>
#include "buttons.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"

unsigned char siren_on = 0;
unsigned char light_show_on = 0;
unsigned char song_on = 0;
unsigned char turnoff_on = 0;

void selectFunction()
{
  //If button 4 is pressed,all leds and the buzzer is turned off
  if(sw4_state_down){
    light_show_on = 0;
    song_on = 0;
    siren_on = 0;
    turnoff_on = 1;
    
  }
  //If button 3 is pressed, the paradiddle state machine is started
  if(sw3_state_down){
    light_show_on = 1;
    song_on = 0;
    siren_on = 0;
    turnoff_on = 0;
  }

  //If button 2 is pressed, a song is played
  if(sw2_state_down){
    light_show_on = 0;
    song_on = 1;
    siren_on = 0;
    turnoff_on = 0;
  }

  //If button 1 is pressed a whistle occurs
  if(sw1_state_down){
    light_show_on = 0;
    song_on = 0;
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
}

int blinkLimit = 5;  // duty cycle = 1/blinkLimit
int blinkCount = 0;  // cycles 0...blinkLimit-1
int blinkCount2 = 7; // cycles blinkLimit -1...0
int secondCount = 0; // state var representing repeating time 0…1s

void light_show()
{
    // handle blinking
    blinkCount ++;
    blinkCount2 --;
    if (blinkCount >= blinkLimit) { // on for 1 interrupt period
      blinkCount = 0;
      P1OUT |= LED_GREEN;
    } else {
      // off for blinkLimit - 1 interrupt periods
      P1OUT &= ~LED_GREEN;
    }

    if(blinkCount2 <= 0){
      blinkCount2 = blinkLimit;
      //P1OUT |= LED_RED;
      P1OUT &= ~LED_RED;
    }else{
      //P1OUT &= ~LED_RED;
      P1OUT |= LED_RED;
    }

    // measure a second
    secondCount ++;
    if (secondCount >= 250) {  // once each second
      secondCount = 0;
      blinkLimit ++;         // reduce duty cycle
      if (blinkLimit >= 8)     // but don't let duty cycle go below 1/7.
        blinkLimit = 0;
    }
}
void song(){
    // play song
}
