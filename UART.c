/*
CSE318 - Microcontrollers
UART.c File
*/

#include "UART.h"

#ifndef UART_C
#define UART_C

void PORTE_InitForUART(void)
{
  // INITIALIZING PORTE WITH NEEDED FUNCTIONALITIES
  
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // Inializing PORTA with Clock Gating Control
  
  // Wait for stabilization
  while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R4) == SYSCTL_RCGCGPIO_R4));
  
  GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;         // Unlocking CR Register with Magic Code
  GPIO_PORTE_CR_R = 0x0000000FFU;            // If Not Already Unlocked
  
  //Initializing For UART
  GPIO_PORTE_DEN_R |= 0x30U;                 // Digital Enabling
  GPIO_PORTE_AFSEL_R |= 0x30U;               // GPIO Alternative Function Select
  GPIO_PORTE_PCTL_R  |= (GPIO_PCTL_PE4_U5RX|GPIO_PCTL_PE5_U5TX);           // Configuring pins E4 and E5 for UART
  
}

void PORTA_InitForUART(void)
{
  // INITIALIZING PORTA WITH NEEDED FUNCTIONALITIES

  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;  // Inializing PORTA with Clock Gating Control

  // Wait for stabilization
  while(!((SYSCTL_RCGCGPIO_R & SYSCTL_RCGCGPIO_R0) == SYSCTL_RCGCGPIO_R0));

  GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;        // Unlocking CR Register with Magic Code
  GPIO_PORTA_CR_R = 0x0000000FFU;

  GPIO_PORTA_DEN_R = 0x3U;                  // Digital Enabling

  GPIO_PORTA_AFSEL_R |= 0x3U;
  GPIO_PORTA_PCTL_R  |= (GPIO_PCTL_PA0_U0RX|GPIO_PCTL_PA1_U0TX);              // Configuring pins A0 and A1 for UART
}

void UART0_Init(void)
{
  SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;

  // Wait for stabilization
  while(!((SYSCTL_RCGCUART_R & SYSCTL_RCGCUART_R0) == SYSCTL_RCGCUART_R0));

  UART0_CTL_R &= ~(0x1U);                  // Clearing UART0EN bit to disable UART0

  PORTA_InitForUART();

  UART0_IBRD_R = 104;                       // For 9600 BAUD RATE
  UART0_FBRD_R = 11;                        // For 9600 BAUD RATE
  UART0_LCRH_R = 0x60U;
  UART0_CC_R = UART_CC_CS_SYSCLK;                        // Clock source is system clock

  UART0_CTL_R |= 0x301U;                    // Setting UART0EN bit to enable UART0
}

uint8_t UART0_inChar(void)
{
  char recievedChar;
  while((UART0_FR_R & 0x10) != 0);          // Wait until the Rx buffer isn't empty  
  recievedChar = UART0_DR_R;                // Read the UART data register
  return recievedChar;
}

void UART0_outChar(uint8_t transmittedChar)
{
  while((UART0_FR_R & 0x20) != 0);          // Wait until Tx buffer not full 
  UART0_DR_R = transmittedChar;   
}

void UART5_Init(void)
{
  SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5;

  // Wait for stabilization
  while(!((SYSCTL_RCGCUART_R & SYSCTL_RCGCUART_R5) == SYSCTL_RCGCUART_R5));

  PORTE_InitForUART();

  UART5_CTL_R &= ~(0x1U);                  // Clearing UART5EN Bit to Disable UART5

  UART5_IBRD_R = 104;                      // For 9600 Baud Rate
  UART5_FBRD_R = 11;                       // For 9600 Baud Rate
  UART5_LCRH_R = 0x60U;
  UART5_CC_R = UART_CC_CS_SYSCLK;          // Clock Source is System Clock

  UART5_CTL_R |= 0x301U;                   // Setting UART5EN Bit to Enable UART5
}

uint8_t UART5_inChar(void)
{
  char recievedChar;
  while((UART5_FR_R & 0x10) != 0);          // Wait until the Rx buffer isn't empty
  recievedChar = UART5_DR_R;                // Read the UART data register
  return recievedChar;
}

void UART5_outChar(uint8_t transmittedChar)
{
  while((UART5_FR_R & 0x20) != 0);          // Wait until Tx buffer not full
  UART5_DR_R = transmittedChar;
}


void printText(char* textToPrint)
{
  int i = 0;
  for (i= 0 ; i< strlen(textToPrint) ; i++)
  {
    UART0_outChar(textToPrint[i]);
  }
}

#endif
