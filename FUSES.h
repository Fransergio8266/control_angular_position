
#pragma config FOSC = HS// CONFIGURADO PRA USAR OSCILADOR 8 MHz
#pragma config WDT = OFF 
#pragma config BOR = OFF //BROWN OUT DESABILITADO          
#pragma config BORV = 0 //NÍVEL DA TENSÃO DE LIMIAR
#pragma config MCLRE = OFF//DESABILITANDO MCLR
#pragma config PWRT = OFF//POWER-UP TIMER DESABILITADO
#pragma config LVP = OFF
//#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
