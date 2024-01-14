#include "app.h"




// Global flag to control the flashing loop

void setup()
{
    // Initialize system clock and peripherals
   // SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
   
    Clock_Init(PORTF);
    GPIO_Config_pin(PORTF,1,1);
    // Configure the GPIO pin as an output
}


int calculateNumOfFlashes(const char *binaryString)
{
    int length = strlen(binaryString);
    int flashes = 0;

    for (int i = 0; i < length; i++)
    {
        if (binaryString[i] == '1')
        {
            flashes = (flashes << 1) | 1;
        }
        else if (binaryString[i] == '0')
        {
            flashes = flashes << 1;
        }
        else
        {
            // Handle invalid characters (if any) in the binary string
            //printf("Invalid character '%c' found in the binary string.\n", binaryString[i]);
            return -1; // Or handle the error in a way that makes sense for your application
        }
    }

    return flashes;
}

void transmitFlashes(int numFlashes)
{
      //printf("Number of flashes: %d", numFlashes);
    // Flash the LED multiple times based on the calculated number of flashes
    for (int i = 0; i < numFlashes; i++)
    {
        GPIO_WritePin(PORTF, 1, 1);                       // Turn on the LED
        TIMER1A_DELAY_MS(8);               // Delay for a while
        GPIO_WritePin(PORTF, 1, 0);                      // Turn off the LED
        TIMER1A_DELAY_MS(8);               // Delay for a while
    }
}

void Arduino_send_message(const char *binaryString)
{
    
    int calculatedFlashes = calculateNumOfFlashes(binaryString);

    // Transmit flashes based on the calculated value
    transmitFlashes(calculatedFlashes);
   
}