/*
CSE318 - Microcontrollers
Interface.h File
*/

#include "tm4c123gh6pm.h"
#include "UART.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef INTERFACE_H
#define INTERFACE_H

extern void PORTD_Init(void);
extern void PORTE_Init(void);
extern void ReadInput(void);
extern void ReadLimits(void);
extern void ReadLock(void);
extern void AnalyzeOperation(void);
extern void TransmitOutput(void);
extern void delay(void);

#endif
