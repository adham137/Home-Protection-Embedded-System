#include "systick.h"



void SysTickDisable (void){
  Clear_Bit(NVIC_ST_CTRL_R,0);
}

void SysTickEnable (void)
{
  NVIC_ST_CTRL_R |= 0x07;
}

uint32 SysTickPeriodGet (void)
{
  
  return  (NVIC_ST_CURRENT_R / CLOCK_FREQ);
  

}
void SysTickPeriodSet (uint32 ui32Period)
{
    NVIC_ST_RELOAD_R = (ui32Period * CLOCK_FREQ);
}

uint32 SysTickValueGet (void)
{
  
 return NVIC_ST_RELOAD_R;
  
} 
  
uint8 SysTick_Is_Time_out(void)
{
return GET_BIT(NVIC_ST_CTRL_R,16);
  
  
}

void SysTick_Handler(void){
  volatile uint8 flag = 0;
volatile uint8 counter = 0;
  if(counter < 5){
    counter++;
  } else{
    if(flag == 1){
    GPIO_WritePort(PORTF , 0x0E);//White LED
    flag = 0;
  } else {
    GPIO_WritePort(PORTF , 0);// LED OFF
    flag = 1;
  }
  counter = 0;
  }
      
}
