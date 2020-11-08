/*
CSE318 - Microcontrollers
UART.h File
*/

#ifndef UART_H
#define UART_H

#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

extern void PORTA_InitForUART(void);
extern void PORTE_InitForUART(void);

extern void UART0_Init(void);
extern void UART0_outChar(uint8_t);
extern uint8_t UART0_inChar(void);

extern void UART5_Init(void);
extern void UART5_outChar(uint8_t);
extern uint8_t UART5_inChar(void);

extern void printText(char*);

#endif

