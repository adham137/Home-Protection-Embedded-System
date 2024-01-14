#include "magnetic.h"

void magnetic_init()
{
  Clock_Init(PORTA);
  //GPIO_Config_pin(PORTC , 6 , 0);
  
  GPIO_PORTA_CR_R = 0x04;
  GPIO_PORTA_DIR_R = 0x00;
  GPIO_PORTA_DEN_R = 0x04;
  
  
}



uint8 magnetic_read()
{
  
       return GET_BIT(GPIO_PORTA_DATA_R, 2);

  
}
