
/*-------------------------------------------------------------------
* Dan Aldridge
* Lab 9 assignment: 1
* Friday Lab session 3:55-6:50
* 10/17/16
* Lee Seemann
* Depending on the character sent through hyperterminal will determine what mode LED3 is set in
* We send a character through hyperterminal. Depending on the character we test in a switch 
statement to see if it is one of the characters that will place LED3 in a mode. The desired inputs 
are a , b , c , d , or e. 
a ----- LED3 STATE == OFF
b ----- LED3 STATE == ON
c ----- LED3 STATE == Blinking at 1Hz
d ----- LED3 STATE == Blinking at 10Hz
e ----- LED3 STATE == Blinking at 50Hz
*---------------------------------------------------------------------*/


#include  "msp430xG46x.h"
#include <stdio.h>

#define LED_ON_STATE	0x31    // character '1'
#define LED_OFF_STATE   0x30	// character '0'
#define LED_NUL_STATE   0x00	// character NULL - used for dummy write operation
#define LED_1HZ_STATE   0x32      // character ‘c’
#define LED_10HZ_STATE  0x33     // character ‘d’
#define LED_50HZ_STATE  0x34     // character ‘e’


#define LED_ON      	0x01		// on
#define LED_OFF     	0x00		// off

unsigned char ch;  			// hold char from UART RX
unsigned char rx_flag;   		// receiver rx status flag

char gm1[] = "Press 'a','b','c','d', or 'e' to set the mode for LED3";	// 55 chars.
char gm2[] = "Type in 'a','b','c','d', or 'e'!";                      	// 33 chars
char gm3[] = "Current LED3 state: ON";                              	// 23 chars
char gm4[] = "Current LED3 state: OFF";                             	// 24 chars
char gm5[] = "Current LED3 state: Blinking at 1Hz";                  	// 36 chars
char gm6[] = "Current LED3 state: Blinking at 10Hz";                 	// 37 chars
char gm7[] = "Current LED3 state: Blinking at 50Hz";                 	// 37 chars


void SPISetup(void)
{
  UCB0CTL0 = UCMSB + UCMST + UCSYNC;     // sync. mode, 3-pin SPI, Master mode, 8-bit data
  UCB0CTL1 = UCSSEL_2 + UCSWRST;  	 // SMCLK and Software reset             	 
  UCB0BR0 = 0x02;    		 	// Data rate = SMCLK/2 ~= 500kHz                     	 
  UCB0BR1 = 0x00;
  P3SEL |= BIT1 + BIT2 + BIT3;   	 	// P3.1,P3.2,P3.3 option select          	 
  UCB0CTL1 &= ~UCSWRST;    	 	// **Initialize USCI state machine**
}

unsigned char SPIGetState(void)
{
	while((P3IN & 0x01));         			// Verifies busy flag
	IFG2 &= ~UCB0RXIFG;    
	UCB0TXBUF = LED_NUL_STATE;    	// Dummy write to start SPI
	while (!(IFG2 & UCB0RXIFG));  		// USCI_B0 TX buffer ready?
	return UCB0RXBUF;             	 
}

void SPISetState(unsigned char State)
{
   while(P3IN & 0x01);            			// Verifies busy flag
   IFG2 &= ~UCB0RXIFG;  
   UCB0TXBUF = State;             		//  write new state
   while (!(IFG2 & UCB0RXIFG));   		// USCI_B0 TX buffer ready?
}

void UART0_putchar(char c) {
  						// wait for other character to transmit
  while (!(IFG2 & UCA0TXIFG));
  UCA0TXBUF = c;
}

void Serial_Initialize(void)
{
  P2SEL |= BIT4+BIT5;    		 // Set UC0TXD and UC0RXD to transmit and receive data
  UCA0CTL1 |= BIT0;    	 	// Software reset
  UCA0CTL0 = 0;    	 		// USCI_A0 control register
  UCA0CTL1 |= UCSSEL_2;    	 // Clock source SMCLK - 1048576 Hz
  UCA0BR0=54;    		 	// baud rate - 1048576 Hz / 19200
  UCA0BR1=0;    		 	//
  UCA0MCTL=0x0A;    	 	// Modulation
  UCA0CTL1 &= ~BIT0;    	 	// Software reset
  IE2 |=UCA0RXIE;           		// Enable USCI_A0 RX interrupt
}

void main(void)
{
 
  WDTCTL = WDTPW+WDTHOLD;           	// Stop watchdog timer
						// Call functions
  Serial_Initialize();   
  SPISetup();
 
  _EINT();   			   // Enable global interrupts
 
  for (int z = 100; z > 0; z--);        // Delay to allow baud rate stabilize
 
  // Greeting Message
  for(int i = 0; i < 55; i++) {
    	ch = gm1[i];
    	UART0_putchar(ch);      // print the greeting message on hyperterminal
	}
  UART0_putchar('\n');	// newline
  UART0_putchar('\r');		// carriage return
 
  while(1)
  {
 
	while(!(rx_flag&0x01)); // wait until receive the character from HyperTerminal
	rx_flag = 0;        	// clear rx_flag
    
	switch (ch)
	{
	case  'a' :				// LED OFF Case
          	SPISetState(LED_OFF_STATE);	// Set
          	//for(int i = 1000; i > 0;i--); //delay
          	//UART0_putchar(SPIGetState());  // prints the current state of LED
         					   	// '1' - ON ; '0' - OFF
          	for(int q = 0; q <= 23; q++)
          	{					// print message to hyperterm.
                    	ch = gm4[q];
                    	UART0_putchar(ch);
          	}
          	UART0_putchar('\n');	// newline
          	UART0_putchar('\r');	// carriage return	 
      	break;
	case  'b' :				// LED ON CASE
          	SPISetState(LED_ON_STATE);	// Set
          	//for(int i = 1000; i > 0;i--); //delay
          	//UART0_putchar(SPIGetState()); 	// prints the current state of LED
   				 		// '1' - ON ; '0' - OFF
           	for(int w = 0; w <= 22; w++)
           	{					// print message to hypterm.
                    	ch = gm3[w];
                    	UART0_putchar(ch);
           	}
           	UART0_putchar('\n');	// newline
           	UART0_putchar('\r');	// carriage return	 
      	break;
	case 'c'  :				// LED 1Hz Toggle Case
          	SPISetState(LED_1HZ_STATE);	// Set
          	//for(int i = 1000; i > 0;i--); //delay
          	//UART0_putchar(SPIGetState()); 	// prints the current state of LED
   				 		// '1' - ON ; '0' - OFF
          	for(int e = 0; e <= 35; e++)
          	{					// print message to hyperterm.
                    	ch = gm5[e];
                    	UART0_putchar(ch);
          	}
          	UART0_putchar('\n');	// newline
          	UART0_putchar('\r');	// carriage return    
       	break;
	case 'd'  :				// LED 10Hz Toggle Case
          	SPISetState(LED_10HZ_STATE);	// Set
          	//for(int i = 1000; i > 0;i--); //delay
          	//UART0_putchar(SPIGetState()); 	// prints the current state of LED
   				 		// '1' - ON ; '0' - OFF
          	for(int r = 0; r <= 36; r++)   	 
          	{					// print message to hyperterm.
                    	ch = gm6[r];
                    	UART0_putchar(ch);
          	}
          	UART0_putchar('\n');	// newline
          	UART0_putchar('\r');	// carriage return  
       	break;
	case 'e'  :				// LED 50Hz Toggle Case
          	SPISetState(LED_50HZ_STATE);	// Set
          	for(int i = 1000; i > 0;i--); //delay
          	//UART0_putchar(SPIGetState()); 	// prints the current state of LED
   				 		// '1' - ON ; '0' - OFF
          	for(int t = 0; t <= 36; t++)
          	{					// print message to hyperterm.
                    	ch = gm7[t];
                    	UART0_putchar(ch);
          	}
          	UART0_putchar('\n');	// newline
          	UART0_putchar('\r');	// carriage return   
       	break;
	default 	:
            	for(int i = 0; i < 33; i++) {
                	ch = gm2[i];
                	UART0_putchar(ch); 		// print the default message on hyperterminal
            	}
            	UART0_putchar('\n');	// newline
            	UART0_putchar('\r');	// carriage return
      	break;
	}
  }
}

// Interrupt for USCI Rx
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIB0RX_ISR (void)
{
  ch = UCA0RXBUF;  				// character received is moved to a variable
  rx_flag=0x01;      				// signal main function receiving a char
}


