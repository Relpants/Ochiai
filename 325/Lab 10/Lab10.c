
/*-------------------------------------------------------------------
* Dan Aldridge
* Lab 10 assignment: 1
* Friday Lab session 3:55-6:50
* 10/27/16
* Lee Seemann
* Use the accel. to hook up to serial app and plot x,y,z  
* In addition to code changes we use x,y,z pins and plug into H8 port on pin 
H8
-----
1-x
2-y
3-z

JTAG2
------
2- Vcc
9-GnD
We then get voltage and ground from the JTAG2 port from the msp430 2013 chip. These changes
allow us to do an ADC converter and plot the result on the myserial ap
*---------------------------------------------------------------------*/

#include <msp430xG46x.h>

void turn_off();
void sendData();
void UART_putchar(char);
void initializeUART();

volatile long int ADCXval, ADCYval, ADCZval; //Vars used to hold vals in ADC interrupt
volatile float Xper, Yper, Zper;          // Calc. units of grav.

void main(void)
{
  WDTCTL = WDTPW +WDTHOLD;              // Stop WDT
  
  initializeUART();	                // Setup UART for RS-232
  
  P6DIR &= ~0x07;	                // Configure P6.0 and P6.1 and P6.2 as input pins             
  P6SEL |= 0x07;	               // Configure P6.0 and P6.1 and P6.2 as analog pins               

  //Set up timer to send ADC info to PC overy 100 ms
  TACCR0 = 3277;                        //3277 / 32768 Hz = 0.1s
  TACTL = TASSEL_1 + MC_1;              //ACLK, up mode  
  TACCTL0 = CCIE;                       //enabled interupt

  //Set up ADC 12
  ADC12CTL0 = ADC12ON + SHT0_6 + MSC;   // configure ADC converter
  ADC12CTL1 = SHP + CONSEQ_1;           // Use sample timer, single sequence
  ADC12MCTL0 = INCH_0;                  // ADC chan 0 is A3 pin - Stick X-axis
  ADC12MCTL1 = INCH_1;                  // ADC chan 1 is A7 pin - Stick Y-axis
  ADC12MCTL2 = INCH_2 + EOS;
				                                  //EOS - End of Sequence for Conversions	
  ADC12IE |= 0x01;                        // Enable ADC12IFG.8
  for (int i = 0; i < 0x3600; i++);       // Delay for reference start-up
  ADC12CTL0 |= ENC;                       // Enable conversions
  
  _EINT();                                  // Enable interrupts
  
  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start conversions 
    __bis_SR_register(LPM0_bits + GIE);	    // enter LPM0
  }

}

///////////////////////////////////////////////////////////////////////////////
// User-defined function definitions
///////////////////////////////////////////////////////////////////////////////

void UART_putchar(char c)
{
    while(!(IFG2 & UCA0TXIFG)); //Wait for previous character to be sent
    UCA0TXBUF = c;              //Send byte to the buffer for transmitting
}

//Initializes UART control registers for transmitting data, as well as baud rate
void initializeUART(void)  
{
  
  P2SEL |= BIT4 + BIT5;          //Set up Rx and Tx bits
  UCA0CTL0 = 0;                  //Set up default RS-232 protocol         
  UCA0CTL1 |= BIT0 + UCSSEL_2;   //Disable device, set clock
  UCA0BR0 = 27;                  //1048576 Hz / 38400 = 54.5
  UCA0BR1 = 0;
  UCA0MCTL = 0x94;
  UCA0CTL1 &= ~BIT0;             //Start UART device
}

void sendData(void)
{
  Xper = ((ADCXval-2048)*3/(.3*4096));        //calculate percentage outputs
  Yper = ((ADCYval-2048)*3/(.3*4096));
  Zper = ((ADCZval-2048)*3/(.3*4096));
  
  int i;
  
  //Send packet via rs-232
  UART_putchar(0x55);                   //send header

  //Use character pointers to send one byte of float X and Y and Z value at a time
  char *xpointer=(char *)&Xper;
  char *ypointer=(char *)&Yper;
  char *zpointer=(char *)&Zper;
  
  //Send x percentage float one byte at a time
  for(i=0; i<4; i++)
  {
    UART_putchar(xpointer[i]);
  }
  
  //Send y percentage float one byte at a time
  for(i=0; i<4; i++)
  {
    UART_putchar(ypointer[i]);
  }
  
  //Send z percentage float one byte at a time
  for(i=0; i<4; i++)
  {
    UART_putchar(zpointer[i]);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Interrupt service routines
///////////////////////////////////////////////////////////////////////////////

#pragma vector=ADC12_VECTOR               // Analog to Digital interrupt
__interrupt void ADC12ISR(void)
{
  ADCXval = ADC12MEM0;                    // Move results, IFG is cleared
  ADCYval = ADC12MEM1;
  ADCZval = ADC12MEM2;
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}

#pragma vector = TIMERA0_VECTOR           // Timer A interrupt
__interrupt void timerA_isr()
{
  sendData();                             // Call sendData function
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPM0
}
