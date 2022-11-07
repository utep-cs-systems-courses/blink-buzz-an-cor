#include <msp430.h>
#include "buttons.h"


// handles switches interrupts on greenboard(p2)
void __interrupt_vec(PORT2_VECTOR) Port_2(){

  if (P2IFG & SW1) { //checks whether button caused interrupt

    P2IFG &= ~SW1; // clears switch interrupt
    sw1_interrupt_handler(); // switch handler
  }
}
