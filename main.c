/* 
 * File:   main.c
 * Author: ASUS
 *
 * Created on 21 de Abril de 2020, 11:48
 */

#include <stdio.h>
#include <stdlib.h>
#include "FUSES.h"
#include "uart.h"
#include "i2c.h"
#include "mpu.h"
#include "pwm_funct.h"
#include <xc.h>
//int dc=0;//sinal de controle convertido em ciclo de trabalho
float erro;
float u=0;//controle
float k=0.3;//constante de ganho proporcional
signed char buf[15]/*{'5','6','4','/0'}*/;
 int dc=70;//ciclo de trabalho inicial
void  __interrupt(high_priority) myHighIsr(void)
 {
    
pwm_dc(dc);

  
TMR0L=0xFE;
TMR0H=0xFF;    

TMR0IF=0;
}

void main(void) {
    ADCON1=0b00001111;
    pwm_config();    
    //CONFIGURA UART PARA 9600 bits high speed assíncrono
    uart_init();
i2c_mestre_config();
   mpu_config();
GIE=1;
PEIE=1;
//valor inicial do servo motor
     
    while(1){
        float ang=0;
      int set_point=0;
      
     CREN=1;//religar buffer de recpeção
    
     set_point=uart_ler_string();
    //if(set_point>9)
     //else{;}
     CREN=0; //limpa buffer de recepção
        
      
         ang=mpu_ler();  
      erro=set_point-ang;
      u=-k*erro;//maior sinal de controle inclina para angulo negativo
      dc=dc+(int)u;
      
   //   limitador do sinal de controle
if(dc>99){
dc=99;}
else if (dc<35){dc=35;}       

        //else{  dc=serial_dc;}

 // if(serial_dc>99){
//dc=99;}
//else if (serial_dc==0 || serial_dc<35){;}       
//else{  dc=serial_dc;}
       
      
   //uart_escreve_byte('\t');
   sprintf(buf,"%0.2f/%d",ang,set_point); 
         // sprintf(buf,"%d",set_point);
    uart_escreve_string(buf);
   
    uart_escreve_byte('\n');    
        
        __delay_ms(2);
          
    }
     //return;
}

