#include"GPIO.h"

void Clock_Init(uint8 port)
{
  switch(port)
  {
        case PORTA:
        SYSCTL_RCGCGPIO_R |= PORTA;
        while(( SYSCTL_PRGPIO_R & PORTA ) == 0 ) {}
        GPIO_PORTA_LOCK_R = 0X4C4F434B;
        break;
    
        case PORTB:  
        SYSCTL_RCGCGPIO_R |= PORTB;
        while(( SYSCTL_PRGPIO_R & PORTB ) == 0 ) {}
        GPIO_PORTB_LOCK_R = 0X4C4F434B;
        break;

        
        case PORTC:  
        SYSCTL_RCGCGPIO_R |= PORTC;
        while(( SYSCTL_PRGPIO_R & PORTC ) == 0 ) {}
        GPIO_PORTC_LOCK_R = 0X4C4F434B;
        break;
        
        case PORTD:  
        SYSCTL_RCGCGPIO_R |= PORTD;
        while(( SYSCTL_PRGPIO_R & PORTD ) == 0 ) {}
        GPIO_PORTD_LOCK_R = 0X4C4F434B;
        break;
        
        case PORTE:  
        SYSCTL_RCGCGPIO_R |= PORTE;
        while(( SYSCTL_PRGPIO_R & PORTE ) == 0 ) {}
        GPIO_PORTE_LOCK_R = 0X4C4F434B;
        break;
        

        case PORTF:  
        SYSCTL_RCGCGPIO_R |= PORTF;
        while(( SYSCTL_PRGPIO_R & PORTF ) == 0 ) {}
        GPIO_PORTF_LOCK_R = 0X4C4F434B;
        break;
         
  
  }
  
}
void GPIO_Config_pin(uint8 Port , uint8 Pin , uint8 Direction)
{
    if(Port==PORTA || Port==PORTB || Port==PORTC || Port==PORTD || Port==PORTE || Port==PORTF)
    {
        if(Pin<8)
        {
            switch(Port)
            {
            case PORTA:
                GPIO_PORTA_CR_R  |= 1<<Pin;
                GPIO_PORTA_DEN_R |= 1<<Pin;

                if(Direction==0)
                {
                    GPIO_PORTA_DIR_R &= ~(1<<Pin);
                    GPIO_PORTA_PUR_R |= (1<<Pin);
                }
                else if(Direction==1) //output
                {
                    GPIO_PORTA_DIR_R |= (1<<Pin);
                }
                

                break;

            case PORTB:
                GPIO_PORTB_CR_R  |= 1<<Pin;
                GPIO_PORTB_DEN_R |= 1<<Pin;

                if(Direction==0)
                {
                    GPIO_PORTB_DIR_R &= ~(1<<Pin);
                    GPIO_PORTB_PUR_R |= (1<<Pin);
                }
                else if(Direction==1)
                {
                    GPIO_PORTB_DIR_R |= (1<<Pin);
                }
            
                break;

            case PORTC:
                GPIO_PORTC_CR_R  |= 1<<Pin;
                GPIO_PORTC_DEN_R |= 1<<Pin;

                if(Direction==0)
                {
                    GPIO_PORTC_DIR_R &= ~(1<<Pin);
                    GPIO_PORTC_PUR_R |= (1<<Pin);
                }
                else if(Direction==1)
                {
                    GPIO_PORTC_DIR_R |= (1<<Pin);
                }
               
                break;

            case PORTD:
                GPIO_PORTD_CR_R  |= 1<<Pin;
                GPIO_PORTD_DEN_R |= 1<<Pin;

                if(Direction==0)
                {
                    GPIO_PORTD_DIR_R &= ~(1<<Pin);
                    GPIO_PORTD_PUR_R |= (1<<Pin);
                }
                else if(Direction==1)
                {
                    GPIO_PORTD_DIR_R |= (1<<Pin);
                }
               
                break;

            case PORTE:
                GPIO_PORTE_CR_R  |= 1<<Pin;
                GPIO_PORTE_DEN_R |= 1<<Pin;

                if(Direction==0)
                {
                    GPIO_PORTE_DIR_R &= ~(1<<Pin);
                    GPIO_PORTE_PUR_R |= (1<<Pin);
                }
                else if(Direction==1)
                {
                    GPIO_PORTE_DIR_R |= (1<<Pin);
                }
                
                break;

            case PORTF:
                GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
                GPIO_PORTF_CR_R  |= 1<<Pin;
                GPIO_PORTF_DEN_R |= 1<<Pin;

                if(Direction==0)
                {
                    GPIO_PORTF_DIR_R &= ~(1<<Pin);
                    GPIO_PORTF_PUR_R |= (1<<Pin);
                }
                else if(Direction==1)
                {
                    GPIO_PORTF_DIR_R |= (1<<Pin);
                }
                
                break;

            
        }
     
  
        }
  
}
}
void GPIO_WritePin(uint8 Port , uint8 Pin , uint8 Value)
{
   if(Port==PORTA || Port==PORTB || Port==PORTC || Port==PORTD || Port==PORTE || Port==PORTF)
    {
        if(Pin<8)
        {
            switch(Port)
            {
            case PORTA:
                if(Value==1)
                {
                    GPIO_PORTA_DATA_R |= 1<<Pin;
                }
                else if(Value==0)
                {
                    GPIO_PORTA_DATA_R &= ~(1<<Pin);
                }
                break;
            case PORTB:
                if(Value==1)
                {
                    GPIO_PORTB_DATA_R |= 1<<Pin;
                }
                else if(Value==0)
                {
                    GPIO_PORTB_DATA_R &= ~(1<<Pin);
                }
                break;


            case PORTC:
                if(Value==1)
                {
                    GPIO_PORTC_DATA_R |= 1<<Pin;
                }
                else if(Value==0)
                {
                    GPIO_PORTC_DATA_R &= ~(1<<Pin);
                }
                break;


            case PORTD:
                if(Value==1)
                {
                    GPIO_PORTD_DATA_R |= 1<<Pin;
                }
                else if(Value==0)
                {
                    GPIO_PORTD_DATA_R &= ~(1<<Pin);
                }
                break;

            case PORTE:
                if(Value==1)
                {
                    GPIO_PORTE_DATA_R |= 1<<Pin;
                }
                else if(Value==0)
                {
                    GPIO_PORTE_DATA_R &= ~(1<<Pin);
                }
                break;


            case PORTF:
                if(Value==1)
                {
                    GPIO_PORTF_DATA_R |= 1<<Pin;
                }
                else if(Value==0)
                {
                    GPIO_PORTF_DATA_R &= ~(1<<Pin);
                }
                break;

            }
  }
}
  
  
  
}
void GPIO_WritePort(uint8 Port, uint8 value)
{
    if(Port==PORTA || Port==PORTB || Port==PORTC || Port==PORTD || Port==PORTE || Port==PORTF)
    {
       switch(Port)
            {
            case PORTA:
              GPIO_PORTA_DATA_R = value;
              break;
            case PORTB:
              GPIO_PORTB_DATA_R = value;
              break;
            case PORTC:
              GPIO_PORTC_DATA_R = value;
              break;
            case PORTD:
              GPIO_PORTD_DATA_R = value;
              break;
             case PORTE:
              GPIO_PORTE_DATA_R = value;
              break;
             case PORTF:
              GPIO_PORTF_DATA_R = value;
              break;         
              
            }
           
    }
  
  
  
}

uint8 GPIO_ReadPin(uint8 Port_ID, uint8 pin_num)
{         
    switch(Port_ID)
    {
                case PORTA:
			
                        return (GPIO_PORTA_DATA_R & (1 << pin_num)) >> pin_num;
			break;
		case PORTB:
                        return (GPIO_PORTB_DATA_R & (1 << pin_num)) >> pin_num;
			break;
		case PORTC:
                        return (GPIO_PORTC_DATA_R & (1 << pin_num)) >> pin_num;
			break;
		case PORTD:
                        return (GPIO_PORTD_DATA_R & (1 << pin_num)) >> pin_num;
			break;
                case PORTE:
                        return (GPIO_PORTE_DATA_R & (1 << pin_num)) >> pin_num;
			break;
                 case PORTF:
                        return (GPIO_PORTF_DATA_R & (1 << pin_num)) >> pin_num;
			break;       
                  default:
                      return 2 ;
    }

  
}


uint32 GPIO_ReadPort(uint8 Port_ID)
{
  uint32 value = 0;

		/* Read the port value as required */
    switch(Port_ID)
		{
		case PORTA:
			value = GPIO_PORTA_DATA_R;
			break;
		case PORTB:
			value = GPIO_PORTB_DATA_R;
			break;
		case PORTC:
			value = GPIO_PORTC_DATA_R;
			break;
		case PORTD:
			value = GPIO_PORTD_DATA_R;
			break;
                case PORTE:
			value = GPIO_PORTE_DATA_R;
			break;
                 case PORTF:
			value = GPIO_PORTF_DATA_R;
			break; 
              
                        
                        
		}
	

	return value;
}
