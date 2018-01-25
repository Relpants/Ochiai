
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


#include <msp430xG46x.h>
#include <stdio.h>

#define SW2 (BIT1&P1IN)

unsigned int sec = 0;                       	// Seconds para.
unsigned int min = 0;                       	// Minutes para.
unsigned int hsec = 0;                      	// Hundredths of a Sec. para.

char Time[15];                             	// string to keep current time

void SetTime(void);
void SendTime(void);
void UART_Intialize(void);

void UART_Intialize(void)
{
  P2SEL |= BIT4 + BIT5;                   	//Set UCOTXD and UCORXD to transmit and recieve data
  UCA0CTL1 |= BIT0;                       	// Software reset
  UCA0CTL0 = 0;                           	// USCI_AO control register
  UCA0CTL1 |= UCSSEL_2;                   	// Clock source SMCLK
  UCA0BR0 = 54;                           	// 1048576 Hz / 19200
  UCA0BR1 = 0;
  UCA0MCTL = 0x0A;                        	// Modulation
  UCA0CTL1 &= ~BIT0;                       	// Software reset
}


void SendTime(void)                         	// Function to send Time to hyperterm.
{
  sprintf(Time, "%04d:%04d:%04d have elapsed since SW2 was last pressed",min, sec, hsec); //print time to a string
  for(int i = 0; i < 54; i++)              	 
  {
	while (!(IFG2 & UCA0TXIFG) );
	UCA0TXBUF = Time[i];
  }
  while (!(IFG2 & UCA0TXIFG) );
  UCA0TXBUF = 0x0D;
}


void SetTime(void)                          	// Set time Function
{
  hsec++;                                   	// Start inc hsec
  if(hsec == 100)
  {
	hsec = 0;
	sec++;                              	// Once hsec == 100 == 1 sec
	if (sec == 60)
	{
  	min++;
	}
    
                                      	// Once Sec == 60  == 1 min
	P5OUT ^= BIT1;                      	//
  }
}


#pragma vector = TIMERA0_VECTOR             	// Timer A interrupt
__interrupt void TIMERA_ISA(void)
{
  	SetTime();                          	// Call Function to count Time that will be elapsed between SW2 released
	 
}


#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void)           	// Port1 interrupt
{
 	 
  	P1IFG &= ~(0x03);                    	// Clear P1 IFG
  	P3OUT |= 0x01;                       	// Set P3.0 to 1    
  	_BIC_SR_IRQ(LPM0_bits);

}



void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 	// Stop WatchDog
  UART_Intialize();                         	//
  TACTL = TASSEL_2 + MC_1 + ID_3;
  TACCR0 = 1311;                           	// 100ms interval  needs to be correct
  TACCTL0 = CCIE;
 
 
  P3DIR |= 0x01;                            	// Set P3.0 For output
                         	// P3 = Special Function
  _EINT();
  P1IE |= BIT1;                             	// P1.1 allow interrupts
  P1IES |= BIT1;                            	// P1.1 hi-low edge
  P1IFG &= ~(0x02);                         	// P1.1 IFG cleared
                                  	// Allow interrupts
 
  sprintf(Time, "Please Press Sw2"); //print time to a string
  for(int i = 0; i < 16; i++)              	 
  {
	while (!(IFG2 & UCA0TXIFG) );
	UCA0TXBUF = Time[i];
  }
  while (!(IFG2 & UCA0TXIFG) );
  UCA0TXBUF = 0x0D;
 
  while(1)                                  	// Infinite loop
  {
    	_BIS_SR(LPM0_bits);
   	 
      	SendTime();                       	// Send time over hyperterm.  
      	hsec = 0;                           	// Clear Timers
      	sec = 0;
      	min = 0;
  	while(SW2==0);
      	P3OUT = 0x00;                    	// Set P3.0 to 0
 	 
  }
}
 




