/**
 * Faculty of Engineering - Ain Shams University
 * Mechatronics Engineering and Automation Program
 * CSE318 - Microcontrollers
 * Spring 2019
 *
 * Michael Samy Hannalla - 16P8202
 * Ahmed Amr Bashandy    - 16P3030
 *
 * Final Project
 * Passenger Windows Interfacing
 * Transmitter Microcontroller
 *
 * main.c
 */

#include "UART.h"
#include "Interface.h"
#include "Scheduler.h"
#include "Systick.h"
#include "string.h"
#include "stdio.h"

int main(void)
{
    PORTD_Init();
    PORTE_Init();

    SysTick_Enable();

    UART5_Init();

    while(1)
    {
        Schedule();
    }

	return 0;
}
