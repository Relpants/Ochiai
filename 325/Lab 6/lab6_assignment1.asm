/*-------------------------------------------------------------------
* Dan Aldridge
* Lab 6 assignment: 1
* Friday Lab session 3:55-6:50
* 9/16/16
* Lee Seemann
* This program deals with clock cycle and setting the speed of clock; to later
toggle the blinking of both leds at different rates.
We set the base clock speed to 4MHZ and blink both leds , depending on
which SW is pressed the rate at which the blinking occurs changes
for SW1 it is doubled and SW2 halfed
*---------------------------------------------------------------------*/

#include  <msp430xG46x.h>

#define SW1 BIT0&P1IN               // B1 - P1.0 switch SW1 
#define SW2 BIT1&P1IN               // P1.1 SW2

unsigned long int i = 117647;

void main(void) 
{ 
   WDTCTL = WDTPW + WDTHOLD;        // Stop watchdog timer 
   P2DIR |= 0x06; 		    // Set P2.1 and P2.2 to output direction (0000_0110) 
   P2OUT = 0x02; 	            // Set P2OUT to 0000_0010b (LED2 is ON, LED1 is OFF)
   _EINT();                         // enable interrupts
        
   FLL_CTL0 |= DCOPLUS + XCAP18PF;  // Set load capacitance for xtal
   SCFI0 |= FN_2;                   // x2 DCO, 4MHz nominal DCO
   SCFQCTL = 61;                    // (122+1) x 32768 * 2 = 4Mhz
        
   P1IE |= BIT0;                    // P1.0 interrupt enabled
   P1IES |= BIT0;                   // P1.0 hi/low edge
 //  P1IFG &= ~BIT0;                  // P1.0 IFG cleared
   
   P1IE |= BIT1;                    // P1.1 interrupt enabled
   P1IES |= BIT1;                       
   P1IFG &= ~(0x03);
   
   // long i = ( 2000000 / 5);
 
   
   while(1)                     // loop until interrupt
   {    
     i--;                       // decrement
     if(i==0)                   // check if delay over
     {
        P2OUT ^= 0x06; 		// Toggle P2.1 and P2.2 using exclusive-OR 
        i = 117647;;      // reinitalize i
     }
   } 
}
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void)      // interrupt code below
{  
  //  long i = (2000000 / 5);           // re-intialize i
  
    P1IFG &= ~(0x03);                 // Clear flags
    
    if((SW1) == 0)                    // Logic if SW1 is pressed
    {
      SCFQCTL = 122;                  // (122+1) x 32768  * 2 = 8Mhz
      while((SW1)==0)                 // Continue to blink faster X2 while SW1 pressed
      {
        i--;                          // decrement
        if(i==0)                      // check if "delay over"
        {
          P2OUT ^= 0x06;              // Xor LEDS
          i = 117647;          // re-intialize i for correct delay
        }
      }
       
       SCFQCTL = 61;                 // SW1 no longer pressed reset to org clock speed
    }
    else if((SW2) == 0)              // Logic if SW2 is pressed
    {
      SCFQCTL = 30;                  // (30+1) x 32768  * 2 = 2Mhz
      while((SW2)==0)                // Continue to blink slower while SW2 pressed
      {
        i--;                         // decrement 
        if(i==0)                     // check if "delay over"
        {
          P2OUT ^= 0x06;             // XOR LEDS 
          i = 117647;         // re-initialize i for correct delay
        }
      }
       
       SCFQCTL = 61;                 // SW2 no longer pressed reset to org clock speed
    }
  
}