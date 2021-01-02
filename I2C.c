#include <xc.h>
#include "i2c.h"

void i2c_mestre_config(){
    SSPSTAT=0x80;		/* Slew rate disabled, other bits are cleared */
    SSPCON1=0x28;	/* Enable SSP port for I2C Master mode,
			clock = FOSC / (4 * (SSPADD+1))*/ 
    SSPCON2=0x00;
    SSPADD=((_XTAL_FREQ_I2C/4)/I2C_BaudRate) - 1;;	/* Clock 100 kHz */  
    //SSPIE=1;		/* Enable SSPIF interrupt */
    SSPIF=0;
    SCL=1;
    SDA=1;
}

void i2c_pronto()
{
    while(!SSPIF);                  /* Wait for operation complete */
    SSPIF=0;                        /*clear SSPIF interrupt flag*/
}


void i2c_mestre_aguarda(){
while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

//void i2c_mestre_init(){
//i2c_mestre_aguarda();    
  //SEN = 1;        
    //i2c_mestre_aguarda();
  //  SEN = 1;
    //while(!SSPIF);
    //SSPIF=0;
//}

char i2c_init(char end)
{
    SEN = 1;            /* Send START condition */
    while(SEN);         /* Wait for completion of START */
    SSPIF=0;
    if(!SSPSTATbits.S){              /* Return 0 if START is failed */
    return 0;}
    return (i2c_mestre_escreve(end)); 
    }

char i2c_mestre_escreve(char dado){

 SSPBUF = dado;                /* Write data to SSPBUF */
 i2c_pronto();
 if (ACKSTAT){                  /* Return 2 if acknowledgment received else 1 */
        return 1;}
      else{
        return 2;}    
}

void i2c_init_aguarda(char end){

while(1)
  {   
    SEN = 1;            /* Send START condition */
    while(SEN);         /* Wait for completion of START */
    SSPIF = 0;
    if(!SSPSTATbits.S){              /* Continue if START is failed */
        continue;}
    i2c_mestre_escreve(end); /* Write slave device address with write to communicate */
    if(ACKSTAT)                     /* Check whether Acknowledgment received or not */
    {
        i2c_mestre_para();                 /* If not then initiate STOP and continue */
        continue;
    }    
    break;                          /* If yes then break loop */
  }
}

char i2c_mestre_para(){

    PEN = 1;                        /* Initiate STOP condition */
    while(PEN);                     /* Wait for end of STOP condition */
    SSPIF = 0;
    if(!SSPSTATbits.P){             /* Return 0 if STOP failed */
    return 0;}
}



void i2c_ack(){
    ACKDT=0;//RECEBEU BYTE DO SLAVE
    ACKEN=1;//ENVIA O ACKDT CONFIRMANDO QUE RECEBEU
    while(ACKEN);}

void i2c_nack(){
    ACKDT=1;//NÃO RECEBEU BYTE DO SLAVE
    ACKEN=1;//ENVIA O ACKDT CONFIRMANDO QUE NÃO RECEBEU
    while(ACKEN);}



char i2c_mestre_repeteinit(char end){

    RSEN = 1;                       /* Send REPEATED START condition */
    while(SSPCON2bits.RSEN);        /* Wait for completion of REPEATED START condition */
    SSPIF = 0;
    if(!SSPSTATbits.S){              /* Return 0 if REPEATED START is failed */
    return 0;}
    i2c_mestre_escreve(end);  /* Write slave device address with read to communicate */
    if (ACKSTAT)                    /* Return 2 if acknowledgment received else 1 */
     return 1;
    else
     return 2;
    
}

    
//unsigned char i2c_ler_byte(){
  //  i2c_mestre_aguarda();
    //RCEN=1;//HABILITA:O MESTRE LE DO ESCRAVO
    //while(!SSPIF);//ESPERA TERMINAR LEITURA
    //SSPIF=0;
    //i2c_mestre_aguarda();
    //return SSPBUF;
//}


char i2c_ler(char ACK_NACK)
{  
    //---[ Receive & Return A Byte & Send ACK or NACK ]---
    char dado;
    RCEN = 1;              
    while(!BF);      
    dado = SSPBUF;           
    if(ACK_NACK==0){
        i2c_ack();  }          
    else{
        i2c_nack();}     
    i2c_pronto();   
    return dado;
}
