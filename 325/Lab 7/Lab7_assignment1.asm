
/*-------------------------------------------------------------------
* Dan Aldridge
* Lab 7 assignment: 1
* Friday Lab session 3:55-6:50
* 9/23/16
* Lee Seemann
* Play E Note, Then interrupt to C Note. Toggle LED2 at .5 sec interval
* Using P3 We play the E Note sound. While SW2 is pressed we play C Note.
LED1 gets turned on from the start. When SW1 is pressed we start WatchDog
Timer interval, once interval is kicked off the WatchDog Interrupt code runs
toggle LED1 at .5s interval
*---------------------------------------------------------------------*/


#include <msp430xG46x.h>

#define SW1 (BIT0&P1IN)
#define SW2 (BIT1&P1IN)

void main(void)
{
 
  WDTCTL = WDTPW + WDTHOLD;     	// Stop WatchDog Timer
  TB0CCTL4 = OUTMOD_4;          	// TB0 output is in toggle mode
  TB0CTL = TBSSEL_2 + MC_1;     	// SMCLK is clock source, Continuous mode

  P2DIR |= 0x04;                	// Set P2.2 to output direction (0000_0110)
  P2OUT |= 0x04;                	// Set LED1 to ON
 
  P5DIR |= 0x03;
  P5OUT |= 0x03;
 
  P3DIR |= 0x20;                	// Set P3.2 to output
  P3SEL |= 0x20;                	// Set P3.2  special function
  _EINT();                      	// Enable interrupts
 
  IE1 |= WDTIE;                 	// Enable Watchdog interrupt
 
  P1IE |= BIT0;                 	// P1.0 interrupt enable
  P1IES |= BIT0;                	// P1.0 hi/low edge
  P1IE |= BIT1;                 	// P1.1 interrupt enable
  P1IES |= BIT1;                	// P1.1 hi/low edge   
  P1IFG &= ~(0x03);             	// P1.1 + P1.0 IFG cleared
 
  TA0CCTL0 = CCIE;              	// TA1 count triggers interrupt
  TA0CCR0 = 10000;                	// Set TA1 count value
  TA0CTL = TASSEL_1 | MC_3;     	// AMCLK is clock source, UP/DOWN mode
 
 
  while(1)
  {
	TB0CCR0 = 1500;              	// Play E Note
	TB0CCR4 = 1500;                        	 
	while((SW2) == 0)            	// Check for while Sw2 pressed
	{   
    	TB0CCR0 = 2000;          	// Play C note
    	TB0CCR4 = 2000;
   	 
 	}
    
  }



 
      	 
}
#pragma vector = WDT_VECTOR        	 
__interrupt void watchdog_timer(void)   // WatchDog Timer interrupt code
{
  P1IFG &= ~(0x03);                 	// Clear P1 IFG
  P2OUT ^= 0x04;                    	// Toggle LED1
 
  if((SW1) != 0)                    	// Stop WatchDog Timer if Sw1 Released
  {
  	WDTCTL = WDTPW + WDTHOLD;     	// Stop
  }
   
   			 
}
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void)   	// Port1 interrupt
{
 
	P1IFG &= ~(0x03);               	// Clear P1 IFG
	if((SW1) == 0)                  	// If SW1 pressed set WatchDog Timer
	{
  	WDTCTL = WDT_ADLY_1000;       	// 1s
	}
}
#pragma vector = TIMERA0_VECTOR
__interrupt void TIMERA0_ISR (void)
{
  P5OUT ^= 0x03;            	// Toggle LED4
  TACCTL0 &= ~CCIFG;        	// Clear interrupt flag
}


