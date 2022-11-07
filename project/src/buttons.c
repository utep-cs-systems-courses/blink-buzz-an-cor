#include <msp430.h>
#include "buttons.h"
#include "led.h"
#include "stateMachines.h"


char sw1_state_down, sw1_state_changed,
  sw4_state_down, sw4_state_changed;

// handle when each respective is pressed/unpressed
static char sw1_update_interrupt_sense()
{
  char p2val = P2IN;// switch is in p2
  // Update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SW1);// If switch up, sense down
  P2IES &= (p2val | ~SW1);// If switch down, sense up
  return p2val;
}
static char sw4_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SW4);
  P2IES &= (p2val | ~SW4);
  return p2val;
}

// Initializes switches
void switch_init()
{
  P2REN |= SWITCHES; // Enables resistors for switches
  P2IE |= SWITCHES; // Enable interrupts from switches
  P2OUT |= SWITCHES; // Pull-ups for switches
  P2DIR &= ~SWITCHES; // Set switches' bits for input

  // Detect button presses
  sw1_update_interrupt_sense();
  sw4_update_interrupt_sense();

}

void sw1_interrupt_handler()
{
  char p2val = sw1_update_interrupt_sense();
  sw1_state_down = (p2val & SW1) ? 0 : 1;// 0 when switch is up, otherwise 1 to show button pressed
  sw1_state_changed = 1;//boolean to show if state changed
  selectFunction();//picks method according to switch # pressed
  led_update();//updates leds
}

void sw4_interrupt_handler()
{
  char p2val = sw4_update_interrupt_sense();
  sw4_state_down = (p2val & SW4) ? 0 : 1;
  sw4_state_changed = 1;
  selectFunction();
  led_update();
}
