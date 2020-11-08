/*
CSE318 - Microcontrollers
Systick.h File
*/

#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"


#ifndef SYSTICK_H
#define SYSTICK_H

extern void SysTick_Enable(void);
extern void SysTick_Disable(void);
extern uint32_t SysTickPeriodGet (void);
extern void SysTickPeriodSet(uint32_t);
extern uint32_t SysTickValueGet(void);
extern bool SysTick_TimeOut(void);

#endif
