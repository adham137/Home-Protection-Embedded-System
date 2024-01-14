#include "ultrasonic.h"



/* This function captures consecutive rising and falling edges of a periodic signal */
/* from Timer Block 0 Timer A and returns the time difference (the period of the signal). */
uint32 Measure_distance(void)
{
    int lastEdge, thisEdge;
	
	  /* Given 10us trigger pulse */
	  GPIO_PORTA_DATA_R &= ~(1<<4); /* make trigger  pin high */
	  TIMER1A_DELAY_MS(10); /*10 seconds delay */
	  GPIO_PORTA_DATA_R |= (1<<4); /* make trigger  pin high */
	  TIMER1A_DELAY_MS(10); /*10 seconds delay */
	  GPIO_PORTA_DATA_R &= ~(1<<4); /* make trigger  pin low */

 	while(1)
	{
            TIMER0_ICR_R = 4;            /* clear timer0A capture flag */
            while((TIMER0_RIS_R & 4) == 0) ;    /* wait till captured */
	  if(GPIO_PORTB_DATA_R & (1<<6)) /*check if rising edge occurs */
		{
                lastEdge = TIMER0_TAR_R;     /* save the timestamp */
		/* detect falling edge */
                TIMER0_ICR_R = 4;            /* clear timer0A capture flag */
                while((TIMER0_RIS_R & 4) == 0) ;    /* wait till captured */
                thisEdge = TIMER0_TAR_R;     /* save the timestamp */
		return (thisEdge - lastEdge); /* return the time difference */
		}
	}
}