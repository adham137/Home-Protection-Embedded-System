#ifndef dio_h
#define dio_h


/*************************************************************
*                           Includes
**************************************************************/
#include "..\Types.h"
#include "..\tm4c123gh6pm.h"

/*******************************************************************************
*                                Definitions                                  *
*******************************************************************************/
//#define LOGIC_LOW                       0
#define PORTABase	    	        0x40004000
#define PORTBBase   	                0x40005000
#define PORTCBase       	        0x40006000
#define PORTDBase                 	0x40007000
#define PORTEBase			0x40024000
#define PORTFBase			0x40025000

#define GPIODIR              (( unsigned long)0x400)
#define GPIODEN              (( unsigned long)0x51C)
#define GPIOLOCK             (( unsigned long)0x520)
#define GPIOCR               (( unsigned long)0x524)
#define GPIOAFSEL            (( unsigned long)0x420)
#define GPIOPUR              (( unsigned long)0x510)	
#define GPIOAMSEL            (( unsigned long)0x528)	
#define GPIOPCTL             (( unsigned long)0x52C)
#define GPIODATA             (( unsigned long)0x000)


#define PIN0                	0
#define PIN1                	1
#define PIN2                	2
#define PIN3                	3
#define PIN4            	4
#define PIN5        	        5
#define PIN6    	        6
#define PIN7	                7

#define PORTA                   0x01
#define PORTB                   0x02
#define PORTC                   0x03
#define PORTD                   0x04
#define PORTE                   0x10
#define PORTF                   0x20


typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;



/************************************************************
*Function:Clock_inititialization
*Parameters:Void
*Description : This function initialize the I/O of the microcontroller 
*Return_Value : None 
*************************************************************/
void Clock_Init(uint8 port);



/************************************************************
*Function:DIO_inititialization
*Parameters:Void
*Description : This function initialize the I/O of the microcontroller 
*Return_Value : None 
*************************************************************/
void GPIO_Config_pin(uint8 Port , uint8 Pin , uint8 Direction);

/************************************************************
*Function:DIO_Write Pin
*Parameters:Pointer of the port , pin number , value to write
*Description : This function initialize the I/O of the microcontroller 
* Return Value : None 
*************************************************************/
void GPIO_WritePin(uint8 Port , uint8 Pin , uint8 Value);




/************************************************************
*Function:DIO_Write Port
*Parameters:Void
*Description : This function initialize the I/O of the microcontroller 
* Return Value : None 

*************************************************************/
void GPIO_WritePort(uint8 Port, uint8 value);



/************************************************************
*Function:DIO_Read Pin
*Parameters:Port ID and Pin number to read
*Description :  Read and return the value for the required pin, it should be Logic High or Logic Low.
               If the input port number or pin number are not correct, The function will return Logic Low.
* Return Value : Pin Value 
*************************************************************/

uint8 GPIO_ReadPin(uint8 Port_ID, uint8 pin_num);



/************************************************************
*Function:DIO_Read Port
*Parameters:Port Num
*Description : Read and return the value of the required port.
              If the input port number is not correct, The function will return ZERO value.
* Return Value : Port value  
*************************************************************/

uint32 GPIO_ReadPort(uint8 Port_ID);




#endif