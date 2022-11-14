#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buttons.h"
#include "buzzer.h"

void main(void) 
{
    // Initializes clocks, wd, buzzer, switches, and leds
      configureClocks();
      buzzer_init();
      switch_init();
      led_init();
      enableWDTInterrupts();
      or_sr(0x18);  // CPU off, GIE on
} 
