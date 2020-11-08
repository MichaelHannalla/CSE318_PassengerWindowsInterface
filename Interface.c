/*
CSE318 - Microcontrollers
Interface.h File
*/

#include "Interface.h"

#ifndef INTERFACE_C
#define INTERFACE_C

// INPUT ANALYSIS
bool Move;                      // TRUE FOR PRESSING - FALSE FOR IDLE
bool MoveDirection;             // TRUE FOR UP       - FALSE FOR DOWN
bool DriverOrPassenger;         // TRUE FOR DRIVER   - FALSE FOR PASSENGER
bool UpperLimitIsReached;
bool LowerLimitIsReached;
bool LockIsPressed;
char SelectedOperation;

// ENCODING OF COMMANDS
#define UP_DRIVER                         (0b1110) // Button Connected to PD0
#define DOWN_DRIVER                       (0b1101) // Button Connected to PD1
#define UP_PASSENGER                      (0b1011) // Button Connected to PD2
#define DOWN_PASSENGER                    (0b0111) // Button Connected to PD3
#define CONTROL_BUTTONS_UNPRESSED_STATE   (0b1111) // All Buttons Are Pulled Up

#define UPPER_LIMIT_REACHED               (0b0001) // Button Connected to PE0
#define LOWER_LIMIT_REACHED               (0b0010) // Button Connected to PE1
#define LIMITS_UNREACHED_STATE            (0b0011) // Inverted Logic Because Limit Switches Are Connected at NC Terminals

#define LOCK_UNPRESSED                    (0b0100) // Button Connected to PE2
#define LOCK_PRESSED                      (0b0000)

// ENCODING OF OPERATIONS
#define MOTOR_RUNNING_UP                  ('D')    // DRIVING
#define MOTOR_RUNNING_DOWN                ('R')    // REVERSE
#define MOTOR_UNMOVING                    ('P')    // PARK

void PORTD_Init(void)
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;   // Inializing PORTD with Clock Gating Control

    // Wait for stabilization
    while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R3) == SYSCTL_RCGCGPIO_R3));

    GPIO_PORTD_DIR_R &= ~(0xFU);               // Setting Pins as Inputs
    GPIO_PORTD_DEN_R |= 0xFU;                  // Digital Enabling
    GPIO_PORTD_PUR_R |= 0xFU;                  // Pulling Up
    GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;         // Unlocking CR Register with Magic Code
    GPIO_PORTD_CR_R = 0x0000000FFU;
}

void PORTE_Init(void)
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;   // Inializing PORTE with Clock Gating Control

    // Wait for stabilization
    while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R4) == SYSCTL_RCGCGPIO_R4));

    // Initialzing For Inputs
    GPIO_PORTE_DIR_R &= ~(0x7U);               // Setting Pins as Inputs
    GPIO_PORTE_DEN_R |= 0x7U;                  // Digital Enabling
    GPIO_PORTE_PUR_R |= 0x7U;                  // Pulling Up Pin PE2, PE1, and PE0
    GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;         // Unlocking CR Register with Magic Code
    GPIO_PORTE_CR_R = 0x00000001FU;
}

void ReadInput(void)
{
    switch(GPIO_PORTD_DATA_R & CONTROL_BUTTONS_UNPRESSED_STATE)
    {
    case (UP_DRIVER):      {Move = true; MoveDirection = true;  DriverOrPassenger = true ; break;}
    case (DOWN_DRIVER):    {Move = true; MoveDirection = false; DriverOrPassenger = true ; break;}
    case (UP_PASSENGER):   {Move = true; MoveDirection = true;  DriverOrPassenger = false; break;}
    case (DOWN_PASSENGER): {Move = true; MoveDirection = false; DriverOrPassenger = false; break;}
    default: Move = false;
    }
}

void ReadLimits(void)
{
    switch(GPIO_PORTE_DATA_R & LIMITS_UNREACHED_STATE)
    {
    case (UPPER_LIMIT_REACHED): {UpperLimitIsReached = true; LowerLimitIsReached = false; break;}
    case (LOWER_LIMIT_REACHED): {UpperLimitIsReached = false; LowerLimitIsReached = true; break;}
    default: {UpperLimitIsReached = false; LowerLimitIsReached = false;};
    }
}

void ReadLock(void)
{
    if((GPIO_PORTE_DATA_R & LOCK_UNPRESSED) == 0)
        LockIsPressed = true;
    else
        LockIsPressed = false;
}

void AnalyzeOperation(void)
{
    if(Move)
    {
        if(!(LockIsPressed) || (LockIsPressed && DriverOrPassenger))
        {
            if(MoveDirection)
            {
                if(!(UpperLimitIsReached)) {SelectedOperation = MOTOR_RUNNING_UP;}
                else {SelectedOperation = MOTOR_UNMOVING;}
            }
            else
            {
                if(!(LowerLimitIsReached)) {SelectedOperation = MOTOR_RUNNING_DOWN;}
                else {SelectedOperation = MOTOR_UNMOVING;}
            }
        }
    }

    else SelectedOperation = MOTOR_UNMOVING;
}

void TransmitOutput(void)
{
    UART5_outChar(SelectedOperation);
}


void delay()
{
    int i = 0;
    for (i=0 ; i<8000;i++);
}

#endif
