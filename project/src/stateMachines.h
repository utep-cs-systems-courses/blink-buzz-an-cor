#ifndef stateMachine_included
#define stateMachine_included

// Booleans that hold machine statuses
extern unsigned char siren_on, turnoff_on, light_show_on, song_on;

void selectFunction();
void siren();
void turnoff();
void light_show();
void song();

#endif
