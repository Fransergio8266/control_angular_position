//I2C.h
#ifndef __I2C__
#define __I2C__
#define _XTAL_FREQ_I2C 8000000
#define I2C_BaudRate 100000

#define SCL TRISB1
#define SDA TRISB0

void i2c_mestre_config();
void i2c_pronto();
void i2c_mestre_aguarda();
char i2c_init(char end);
char i2c_mestre_escreve(char dado);
void i2c_init_aguarda(char end);
char i2c_mestre_para();
void i2c_ack();
void i2c_nack();
char i2c_mestre_repeteinit(char end);
char i2c_ler(char ACK_NACK);

#endif