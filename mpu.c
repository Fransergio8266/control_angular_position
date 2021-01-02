#include "mpu.h"
#include <stdio.h>
#include "uart.h"
#include "i2c.h"
#include <math.h>
#include <xc.h>

void mpu_config()
{
  // Power-Up Delay & I2C_Init
  __delay_ms(150);
  // Setting The Sample (Data) Rate. Taxa de amostrgem do giroscópio 8000/7 e acelerometro 1000/7

  
  i2c_init_aguarda(0xD0);
  i2c_mestre_escreve(SMPLRT_DIV);
  i2c_mestre_escreve(0x07);
  i2c_mestre_para();
 
  // Setting The Clock Source. fREQUENCIA INTERNA DE 8 Mhz
  
  i2c_init_aguarda(0xD0);
  i2c_mestre_escreve(PWR_MGMT_1);
  i2c_mestre_escreve(0x01);
  i2c_mestre_para();
  
  // Configure The DLPF. Sem sincronização. Com fs=8khz e menor delay possível dos filtros dgitais do ADC
 i2c_init_aguarda(0xD0);
  i2c_mestre_escreve(CONFIG);
  i2c_mestre_escreve(0x00);
  i2c_mestre_para();
  
  // Configure The ACCEL (FSR= +-2g).SELF-TEST DESABILITADO DOS ACELERôMETROS
  i2c_init_aguarda(0xD0);
  i2c_mestre_escreve(ACCEL_CONFIG);
  i2c_mestre_escreve(0x00);
   i2c_mestre_para();
  // Configure The GYRO (FSR= +-2000d/s). Self-test desabilitado
  i2c_init_aguarda(0xD0);
  i2c_mestre_escreve(GYRO_CONFIG);
  i2c_mestre_escreve(0x18);
  i2c_mestre_para();
  
  // Enable Data Ready Interrupts. iNTERRUPÇÃO GERADAEM INT TODA VEZ QUE OS DADOS SÃO TRANSM. DO MPU
  i2c_init_aguarda(0xD0);
  i2c_mestre_escreve(INT_ENABLE);
  i2c_mestre_escreve(0x01);
  i2c_mestre_para();
  }

float mpu_ler()
{
  //char buffer[6];
  //int Ax,Ay,Az,T,Gx,Gy,Gz;
  int Ay;
  // float ax,ay,az,t,gx,gy,gz;
  float ay;
  // Prepare For Reading, Starting From ACCEL_XOUT_H
  i2c_init_aguarda(0xD0);//acessa mpu
  i2c_mestre_escreve(ACCEL_YOUT_H);//acessa primeiro registrador de leitura
  i2c_mestre_para();
  i2c_init(0xD1);
  //Ax = ((int)i2c_ler(0)<<8) | (int)i2c_ler(0);
  Ay = ((int)i2c_ler(0)<<8) | (int)i2c_ler(1);
  //Az = ((int)i2c_ler(0)<<8) | (int)i2c_ler(0);
 // T  = ((int)i2c_ler(0)<<8) | (int)i2c_ler(0);
  //Gx = ((int)i2c_ler(0)<<8) | (int)i2c_ler(0);
  //Gy = ((int)i2c_ler(0)<<8) | (int)i2c_ler(0);
  //Gz = ((int)i2c_ler(0)<<8) | (int)i2c_ler(1);
  i2c_mestre_para();
 
//  ax=(float)Ax/16384.0;
  ay=(float)Ay/16384.0;
  //az=(float)Az/16384.0;
  //t=(float)T/340.0+36.53;
  //gx=(float)Gx/16.4;
  //gy=(float)Gx/16.4;
  //gz=(float)Gz/16.4;
  
  //sprintf(buffer,"%0.2f/%0.2f/%0.2f/%0.2f/%0.2f/%0.2f/%0.2f//",ax,ay,az,t,gx,gy,gz);
  //sprintf(buffer,"%0.2f",(180*asin(ay))/M_PI);
  //sprintf(buffer,"%d",Ay);
  //uart_escreve_string(buffer);
  return((180*asin(ay))/M_PI);
}