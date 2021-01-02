//uart.h
#ifndef __UART__
#define __UART__

#define _XTAL_FREQ 16000000
#define TX TRISC6
#define RX TRISC7

void uart_init(void);
void uart_escreve_byte(unsigned char);
void uart_escreve_string(char*);
char uart_ler_byte(void);
int uart_ler_string(void);
#endif