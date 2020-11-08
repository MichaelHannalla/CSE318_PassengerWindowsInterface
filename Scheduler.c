/*
CSE318 - Microcontrollers
Scheduler.c File
*/

#include "Tasks.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "Systick.h"

#ifndef SCHEDULER_C
#define SCHEDULER_C

#define INITIALIZE_TO_ZERO 0

void Schedule(){
  
  uint8_t iterator = INITIALIZE_TO_ZERO;
  static uint8_t Tick_Counter = INITIALIZE_TO_ZERO;

  if (SysTick_TimeOut()){
    
    Tick_Counter++;
    
    while(iterator<Num_Of_Tasks)
    {
      if(Tick_Counter % tasks[iterator].period == 0){
        tasks[iterator].code();
      }
      iterator++;
    }
  }
}
#endif
