/*
Michael Samy Hannalla Tofiles - 16P8202
CSE318 - Microcontrollers
Tasks.h File
*/

#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>

typedef struct task_t{
  void (*code) (void);         //Pointer to function.
  uint32_t period;
}task_t;

extern task_t tasks[];
extern const uint8_t Num_Of_Tasks;

#endif
