#ifndef SYSTICK_h
#define SYSTICK_h

#include "..\Types.h"
#include "..\tm4c123gh6pm.h"
#include "..\bitwise_operations.h"
#include "..\MCAL\GPIO.h"



#define CLOCK_FREQ  16000


void SysTickDisable (void);
void SysTickEnable (void);
uint32 SysTickPeriodGet (void);// Function to get the period of the timer
void SysTickPeriodSet (uint32 ui32Period);//: This function set’s the period of timer in ticks
uint32 SysTickValueGet (void); //This function gets the current value of the register
uint8 SysTick_Is_Time_out(void);//This function check the COUNT register in the NVIC_ST_CTRL_R to make sure that the timer has finished counting. 












#endif

