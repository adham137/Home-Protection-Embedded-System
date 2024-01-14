#include "tm4c123gh6pm.h"
#include "Types.h"
#include "bitwise_operations.h"
#include "MCAL\systick.h"
#include "MCAL\uart.h"

#include "MCAL\gptm.h"
#include "HAL\fume.h"
#include "HAL\magnetic.h"
#include "HAL\bluetooth.h"
#include "HAL\ultrasonic.h"


#include <stdio.h> 
#include <string.h>
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h" 
#include "APP\app.h"

/*
   int main()
{
  Clock_Init(PORTF);
    bluetooth_init();
    fume_init();
    magnetic_init();
     GPIO_Config_pin(PORTF , 1 , 1);
      GPIO_Config_pin(PORTF , 2 , 1);
 GPIO_Config_pin(PORTF , 3 , 1);


  	Delay(10); 
  GPIO_WritePin(PORTF,1,0);  //  led off
            GPIO_WritePin(PORTF,2,0);
              GPIO_WritePin(PORTF,3,0);
    
    while(1)
    {
      char c = bluetooh_read();  
         uint8 value = fume_get_value();
      uint8 value_1 =magnetic_read();
        
                if( c=='A'){
                    if(!value && !value_1)
     {
            Bluetooth_Write_String("Mariam both\n");
        
     }
      else if(!value)
      {
     Bluetooth_Write_String("Habiba fume\n");
        
       }
      else if(!value_1)
      {
Bluetooth_Write_String("Osama Magnetic\n");
      }
  
    }   
			
		
		else if( c=='B'){
			Bluetooth_Write_String("Habiba\n");
		}
		else if( c=='C'){
			Bluetooth_Write_String("Osama\n");
		}
		else if( c=='D'){
			Bluetooth_Write_String("Adham\n");
		}
		if( c=='E'){
			Bluetooth_Write_String("Khaled\n");
		}
		else if( c=='F'){
			
			Bluetooth_Write_String("ala allah\n");
		}	

   
     
      
    }
    return 0;
   
}

*/

///////////////////////////////////////////// Prototypes /////////////////////////////////////////////

// Enable portc pins 1, 2, 3 and their interrupts
void enable_push_buttons_interrupts(void);

void GPIO_PORTF_Handler(void);

void InitButtonsWithInterrupts(void) ;

// Add ISR functions for the three buttons (Start, Stop, Mute) **YET TO BE ADDED TO STARTUP CODE**
void portC_push_buttons_ISR(void);
// Button 1 -> interput to set the start_flag = 1
// Button 2 -> interput to set the start_flag = 0
// Button 3 -> interput to toggle the mute_flag

///////////////////////////////////////////// Global Variables /////////////////////////////////////////////

// Flags
int start_flag = 1;
int mute_flag = 0;

// Threshold for ultrasonic sensor
int threshold = 10;

// Timer variables
/* global variables to store and display distance in cm */
uint32_t time; /*stores pulse on time */
uint32_t distance; /* stores measured distance value */
char mesg[20];  /* string format of distance value */

///////////////////////////////////////////// Functions /////////////////////////////////////////////

int main() {
   
  // Initialize portc pins 5, 6, 7 for push buttons
  InitButtonsWithInterrupts();
  
  // Initialize Timer0A in edge edge time
  Timer_init();
  
  // Setup the arduino
  setup();
  
  // Message sent to bluetooth and arduino
  char message[] = "000";
  
  // Initialize sensors
  magnetic_init();
  fume_init();
  //ultrasonic_init();
  uart_init();
  
  while(1){
  
    // Start when start_flag = 1
    while(start_flag == 1){
    
      // Add value of fume sensor to message
      //uint8 val1 = fume_get_value();
      //printf("Fume read: %d \n", val1);
      uint8 val1 = 1;
      message[0] = (val1)? '0' : '1';           
      
      // Add value of magnetic sensor to message
      //uint8 val2 = magnetic_read();
      //printf("Magnetic read: %d \n", val2);
      uint8 val2 = 0;
      message[1] = (val2)? '0' : '1';
      
      // Add value of ultrasonic sensor to message
      // only if distance is less than a ceratin threshold 
      //time = Measure_distance(); /* take pulse duration measurement */ 
      //distance = (time * 10625)/10000000; /* convert pulse duration into distance */
      distance = 10;
      if(distance <= threshold) message[2] = '1';
      
      // Send message to bluetooth and arduino if mute_flag = 0
      if(mute_flag == 0 && message != "000"){
      
       // Bluetooth_Send_Message(message); 
        Arduino_send_message(message);            // **YET TO BE IMPLEMENTED**
     //   printf("%s \n", message);                // Print to terminal 
        TIMER1A_DELAY_MS(30);
        //start_flag = 0;

        
        // Wait 200ms for flashes to be 
        //TIMER1A_DELAY_MS(200);
      }
      strcpy(message, "000");
      
    }
  }
  return 0;
}

void enable_push_buttons_interrupts(void) {
    // Enable the GPIO port C and configure pins 5, 6, and 7 as inputs
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlDelay(3);

    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

    // Enable pull-up resistors for the pins
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Register the interrupt handler function
    GPIOIntRegister(GPIO_PORTC_BASE, portC_push_buttons_ISR);

    // Configure pins 5, 6, and 7 for both edge interrupt detection
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_BOTH_EDGES);

    // Enable interrupts for pins 5, 6, and 7
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

    // Enable the GPIO port C interrupt in the NVIC
    IntEnable(INT_GPIOC);

    // Enable global interrupts
    IntMasterEnable();
}

void portC_push_buttons_ISR(void) {
    uint32_t ui32Status;

    // Read the interrupt status to determine which pin caused the interrupt
    ui32Status = GPIOIntStatus(GPIO_PORTC_BASE, true);

    // Clear the interrupt flag for the pins that caused the interrupt
    GPIOIntClear(GPIO_PORTC_BASE, ui32Status);

    // Check which button caused the interrupt and handle accordingly
    if (ui32Status & GPIO_PIN_5) {
        // Button on pin 5 was pressed
        start_flag = 1;
        printf("Start button is pressed");
    }
    else if (ui32Status & GPIO_PIN_6) {
        // Button on pin 6 was pressed
        start_flag = 0;
        printf("Stop button is pressed");
    }
    else if (ui32Status & GPIO_PIN_7) {
        // Button on pin 7 was pressed
        mute_flag = (mute_flag)? 0 : 1;
        printf("mute button is pressed");
    }

}

void GPIO_PORTF_Handler(void) {  // If interrupt on PF0 or PF4
    if(GPIO_PORTF_MIS_R & (1<<4)) 
    { 
      GPIO_PORTF_ICR_R |= (1<<4); // Clear the interrupt flag
      start_flag = 1;
      printf("Program started\n");
    }
    else if(GPIO_PORTF_MIS_R & (1<<0))
    {
      GPIO_PORTF_ICR_R |= (1<<0); // Clear the interrupt flag
      start_flag = 0;
      printf("Program is stopped\n");
    }
}

void InitButtonsWithInterrupts(void) {
  
    Clock_Init(PORTF);
  
    GPIO_PORTF_CR_R = 0x1F; // Enable GPIOF commits
    GPIO_PORTF_PUR_R = 0x11; // Set GPIOF push button pins to pull-up
    GPIO_PORTF_DIR_R &= ~0x11; // PF4,PF0 are inputs
    GPIO_PORTF_DEN_R |= 0x11; // PF4,PF0 are digital pins
    GPIO_PORTF_IS_R &= ~0x11; // PF0 is edge-sensitive
    GPIO_PORTF_IBE_R &= ~0x11; // PF0 is not both edges
    GPIO_PORTF_IEV_R &= ~0x11; // PF0 falling edge event
    GPIO_PORTF_ICR_R = 0x11; // Clear flags 0
    GPIO_PORTF_IM_R |= (1<<4)|(1<<0); // Arm interrupt on PF0
    
    NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // priority 5
    NVIC_EN0_R = 0x40000000; // enable interrupt 30 in NVIC
    IntMasterEnable(); // Enable global interrupt
}