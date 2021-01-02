#include "uart.h"
#include <xc.h>


void uart_init(void){
   
   TXSTA=0b00100100;
   RCSTA=0b10010000;
SPBRG=51;
TX=1;
RX=1;
}

void uart_escreve_byte(unsigned char dado){
    while(!TRMT);
    TXREG=dado;
}

void uart_escreve_string(char* mens){
    int i=0;
    while(mens[i]!='\0'){
    uart_escreve_byte(mens[i++]);
    }

}

char uart_ler_byte(void){
    char dado='8';
    if(RCIF){
    dado=RCREG;}
    return dado;
}

 int uart_ler_string(void){
  static char dado[6];
       int i=0;
       int c=800;
  //for(c=0;c<400;++c){
    while(c){   
       if(RCIF){dado[i]=RCREG;++i;}
       --c;
    
       if(dado[i-1]=='\r' || dado[i-1]=='\n'){break;}
    //sai do laçio quando nada chega
    
    }
    
return(atoi(dado));
}




