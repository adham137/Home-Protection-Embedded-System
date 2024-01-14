#ifndef gptm_h
#define gptm_h


/*************************************************************
*                           Includes
**************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

#include "GPIO.h"
#include "..\tm4c123gh6pm.h"
#include "..\Types.h"

/*******************************************************************************
*                                Function Prototypes                           *
*****************************************************************************
Timer_init()
Function to initialize the timer
This function is responsible for initializing the timer.
It does not take any parameters and does not return any value. 
Its purpose is to set up the timer for further operations.
****************************************************************/
void Timer_init();


/************************************************************************************
Function to delay for a specified time in milliseconds
TimerDelay(uint32 delay)
This function is used to introduce a delay for a specified time in milliseconds. 
It takes a single parameter delay, which specifies the time to delay in milliseconds. 
The function does not return any value.
***************************************************************************************/
void TimerDelay(uint32 delay);

/*******************************************************************************
Function to start the timer
TimerStart()
The TimerStart() function is used to start the timer. 
It does not take any parameters and does not return any value. 
Its purpose is to initiate the timer counting.
*******************************************************************************/
void TimerStart();

/*******************************************************************************
Function to set the timer value
TimerSet(uint32_t value)
This function is used to set the timer value. 
It takes a single parameter value, which specifies the desired timer value. 
The function does not return any value.
********************************************************************************/
void TimerSet(uint32 value);

/******************************************************************************* 
Function to read the current timer value
TimerRead()
The TimerRead() function is used to read the current value of the timer. 
It does not take any parameters and returns the current timer value as a uint32_t data type.
********************************************************************************/
uint32 TimerRead(void);

/******************************************************************************* 
Function to reset the timer
TimerReset()
This function is responsible for resetting the timer. 
It does not take any parameters and does not return any value. 
Its purpose is to reset the timer to its initial value.
*******************************************************************************/
void TimerReset(void);

/******************************************************************************* 
Function to stop the timer
TimerStop()
The TimerStop() function is used to stop the timer. 
It does not take any parameters and does not return any value. 
Its purpose is to halt the timer counting.
*******************************************************************************/
void TimerStop(void);

void TIMER1A_DELAY_MS(int time);

void Delay_Ms(int time);
#endif