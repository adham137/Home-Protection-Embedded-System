#include "gptm.h"

volatile uint8_t flag = 0;
volatile uint8_t flag_timer1 = 0;

void Timer_init()
{
    SYSCTL_RCGCTIMER_R |= 1;     /* enable clock to Timer Block 0 */
    SYSCTL_RCGCGPIO_R  |= 2;      /* enable clock to PORTB */
    
    GPIO_PORTB_DIR_R   &=    ~0x40;        /* make PB6 an input pin */
    GPIO_PORTB_DEN_R   |=    0x40;         /* make PB6 as digital pin */
    GPIO_PORTB_AFSEL_R |=  0x40;       /* use PB6 alternate function */
    GPIO_PORTB_PCTL_R  &= ~0x0F000000;  /* configure PB6 for T0CCP0 */
    GPIO_PORTB_PCTL_R  |=  0x07000000;
    
	  /* PB2 as a digital output signal to provide trigger signal */
	  SYSCTL_RCGCGPIO_R |= 1;      /* enable clock to PORTA */
	  GPIO_PORTA_DIR_R |=(1<<4);         /* set PB2 as a digial output pin */
	  GPIO_PORTA_DEN_R |=(1<<4);         /* make PB2 as digital pin */

    TIMER0_CTL_R         &= ~1;          /* disable timer0A during setup */
    TIMER0_CFG_R         = 4;            /* 16-bit timer mode */
    TIMER0_TAMR_R        = 0x17;        /* up-count, edge-time, capture mode */
    TIMER0_CTL_R        |=0x0C;        /* capture the rising edge */
    TIMER0_CTL_R        |= (1<<0);           /* enable timer0A */

}

void TIMER1A_DELAY_MS(int time) {
    SYSCTL_RCGCTIMER_R |= 2; /* enable clock to Timer Block 1 */
    TIMER1_CTL_R = 0; /* disable Timer before initialization */
    TIMER1_CFG_R = 0x04; /* 16-bit option */
    TIMER1_TAMR_R = 0x02; /* periodic mode and down-counter */
    TIMER1_TAILR_R = 16000 * time - 1; /* TimerA interval load value reg */
    TIMER1_TAPR_R = 255;                             // Set the prescaler to 1000
    TIMER1_ICR_R = 0x1; /* clear the TimerA timeout flag */
    TIMER1_CTL_R |= 0x03; /* enable Timer A after initialization */

    
    while ((TIMER1_RIS_R & 0x1) == 0) ; /* wait for TimerA timeout flag */
       
   
}

void TimerStart(void)
{
    TIMER0_CTL_R |= TIMER_CTL_TAEN; // Enable Timer0A
}


void TimerStop(void)
{
    TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // Disable Timer0A
}

void TimerReset(void)
{
    TimerStop();
    TimerStart();
}

void TimerSet(uint32 value)
{
    TIMER0_TAILR_R = value; // Set the load value of Timer0A
}

void TimerDelay(uint32 delay)
{
    // Set the timer to the desired delay value
    TimerSet(delay);

    // Start the timer
    TimerStart();

    // Wait until the timer interrupt occurs
    while (!(TIMER0_RIS_R & TIMER_RIS_TATORIS)) {}
}

uint32 TimerRead(void)
{
    return TIMER0_TAR_R; // Read the current value of Timer0A
}



void timer_0_handler(void)
{
    
    // Toggle the red LED
    GPIO_PORTF_DATA_R ^= (1 << 1);
    // Clear the timer interrupt
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;

}

void TIMER0A_INIT(void){
    TIMER0_CTL_R &= ~1;         /* disable timer0A during setup */
    TIMER0_CFG_R = 0x4;           /* 16-bit timer mode */
    TIMER0_TAMR_R = 0x17;       /* up-count, edge-time, capture mode */
    TIMER0_CTL_R |= 0x0C;       /* capture the rising edge */
    TIMER0_CTL_R |= (1<<0);     /* enable timer0A */
}

void Delay_Ms(int time)
{
  int nTicks = (time * 16000) -1;  
  for(int i=0; i<nTicks; i++);
}

