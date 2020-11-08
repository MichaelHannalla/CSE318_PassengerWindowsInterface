/*
CSE318 - Microcontrollers
Tasks.c File
*/

#ifndef TASKS_C
#define TASKS_C

#include "Tasks.h"
#include "Interface.h"
#include "stdio.h"

static void Task1(void)
{
    ReadInput();
}

static void Task2(void)
{
    ReadLimits();
    ReadLock();
}

static void Task3(void)
{
    AnalyzeOperation();
    TransmitOutput();
}

task_t tasks[] = {
  {
    .code = Task1 ,
    .period = 1
  },
  
  {
    .code = Task2 ,
    .period = 2
  },
  
  {
    .code = Task3 ,
    .period = 3
  }
};

const uint8_t Num_Of_Tasks = (uint8_t) sizeof(tasks)/sizeof(task_t);

#endif
