
/*-------------------------------------------------------------------
* Dan Aldridge
* Lab 8 assignment: 1
* Friday Lab session 3:55-6:50
* 10/10/16
* Lee Seemann
* Send character through hyper terminal while SW2 pressed, Also blink LED3 at 1Hz
While SW2 is still pressed.  Once released time elapsed should be displayed in hyperterminal
* We are to use both chips on the MSP430 for this lab. Setting a link using 4618 P3.0 output
to 2013 P1.4 input. The 2013 chip will detect when P1.4 goes high or low *simulating a character
coming through hyperterminal* and adjust LED3 accordingly.
*---------------------------------------------------------------------*/

#include <msp430x20x3.h>
#include <stdio.h>

#define flag (BIT4&P1IN)

unsigned long int i = 10000;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
 
  P1DIR |= 0x01;
  P1OUT |= 0x00;
 
 
  while(1)
  {
	while(flag!=0)
	{
  	i--;
      	if(i == 0)
      	{
        	P1OUT ^= 0x01;
        	i = 10000;
      	}
   
 	 

	}
	P1OUT = 0x00;
  }
}



