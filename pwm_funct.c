#include <xc.h>
#include "pwm_funct.h"

void pwm_config(void){

TRISB&=(0<<5);
PORTB=0b00000000;

T0CON=0b10000000;
TMR0IE=1;
TMR0L=0xFE;
TMR0H=0xFF;    
TMR0IF=0;
}

void pwm_dc(int dc){

static int t=0;
    ++t;

if((t>=0) && (t<=dc))
{PORTB|=(1<<5);}

else if((t>dc) && (t<720))
{PORTB&=(0<<5);}

else {
t=0;
}
}
