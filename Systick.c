/*
CSE318 - Microcontrollers
Systick.c File
*/

#ifndef SYSTICK_C
#define SYSTICK_C

#define SYSTEM_CLK_FREQUENCY 16000 //Clock Speed in kHz
#define SYSTEM_TICK_MS       125   //System ticks every 125 milliseconds

#include "Systick.h"

void SysTick_Enable(void)
{
  NVIC_ST_CTRL_R    = 0x00000005U;
  SysTickPeriodSet(SYSTEM_TICK_MS);
  NVIC_ST_CURRENT_R = 0x0U;
}

void SysTick_Disable(void)
{
  NVIC_ST_CTRL_R &= ~(0x00000001U);
}

void SysTickPeriodSet(uint32_t Period)
{
  NVIC_ST_RELOAD_R  = SYSTEM_CLK_FREQUENCY * Period;  //Period to be entered in milliseconds
  NVIC_ST_CURRENT_R = 0x0U;
}

bool SysTick_TimeOut(void)
{
  if(((NVIC_ST_CTRL_R & 0x00010000) >> 16) == 1)
    return true;
  else return false;
}

uint32_t SysTick_PeriodGet(void)
{
  return (NVIC_ST_RELOAD_R / SYSTEM_CLK_FREQUENCY);
}

uint32_t SysTick_ValueGet(void)
{
  return (NVIC_ST_CURRENT_R / SYSTEM_CLK_FREQUENCY);
}

#endif
