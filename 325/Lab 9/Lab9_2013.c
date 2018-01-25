 
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


#include "msp430x20x3.h"

#define LED_ON_STATE     0x31   // character '1'
#define LED_OFF_STATE   0x30    // character '0'
#define LED_NUL_STATE   0x00    // character NULL - used for dummy write operation
#define LED_1HZ_STATE   0x32    // character 'c'
#define LED_10HZ_STATE  0x33   // character 'd'
#define LED_50HZ_STATE  0x34   // character 'e'


#define LED_ON        0x01     // on
#define LED_OFF       0x00      // off

#define SET_BUSY_FLAG()   P1OUT |= 0x10;
#define RESET_BUSY_FLAG() P1OUT &= ~0x10;

#define SET_LED()     P1OUT |= 0x01;      // set on
#define RESET_LED()   P1OUT &= ~0x01;   // set off
#define TOGGLE_LED()  P1OUT ^= 0x01;    // toggle

unsigned char LEDState;
unsigned char NextState;



unsigned long int i = 100000;       // 1Hz
unsigned long int j = 10000;        // 10Hz
unsigned long int k = 2000;       // 50Hz




void SPISetup(void)
{
 
  USICTL0 |= USISWRST;      //Set UCSWRST -- needed for re-configuration process
  USICTL0 |= USIPE5 + USIPE6 + USIPE7 + USIOE; // SCLK-SDO-SDI port enable,MSB first   
  USICTL1 = USIIE;          // USI  Counter Interrupt enable                           
  USICTL0 &= ~USISWRST;     // **Initialize USCI state machine**
}



void InitComm(void)
{
 USICNT = 8;                            // Load bit counter, clears IFG
 USISRL = LEDState;                     // set LED state
 RESET_BUSY_FLAG();                     // reset busy flag
}

void LEdInit(unsigned char state)       // initalize
{
  if (state == LED_OFF_STATE)           // If LED off
  {
  RESET_LED();                          // Reset  
  LEDState = LED_OFF_STATE; // Set LED to off
  }
  else
  {
  SET_LED();        // Set 
  LEDState = LED_ON_STATE;  // Set LED to on
  }  
  P1DIR |= 0x11;                          //  P1.0,4 output
}

void SystemInit()
{
 
  WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer

 BCSCTL1 = CALBC1_1MHZ;             // Set DCO
 DCOCTL = CALDCO_1MHZ;
}

void main(void)
{
 
  WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
  LEdInit(LED_OFF_STATE);           //LED state initialization
  SPISetup();                         //USi module in SPI mode initialization
  InitComm();                         //Communication initialization
 
  _EINT();          // Enable interrupts
  while(1)          // infinite loop
  {
   // _BIS_SR(LPM0_bits + GIE);           // Enter LPM0 w/ interrupt
 
  switch (NextState)
  {
    case 0x00 :
      break;
    default :
      LEDState = NextState;         // new state
      break;
  }    
  if (LEDState == LED_OFF_STATE)  // If LED off
  {
    RESET_LED();      // Reset
  }
  else if (LEDState == LED_1HZ_STATE) // If LED toggling 1Hz
  {                      // decrement
    i--;  
    if(i == 0)                       // is “delay” 0
    {
        TOGGLE_LED();                    // XOR
        i = 100000;            // reinitialize i
      }
       
  }
  else if (LEDState == LED_10HZ_STATE)  // if LED toggling 10hz
  {           // decrement
      j--;
      if(j == 0)          // is “delay” 0
      {
        TOGGLE_LED();       // XOR
        j = 10000;          // reinitialize j
      }
       
  }
  else if (LEDState == LED_50HZ_STATE)  // if LED toggling 50Hz
  {           // decrement
      k--;
      if(k == 0)          // is “delay” 0
      {
        TOGGLE_LED();       // XOR
        k = 2000;         // reinitialize k
      }
  }
  else if (LEDState == LED_ON_STATE)  // if LED is ON 
  {
    SET_LED();          // turn on
  }  
  USISRL = LEDState;          // prepares new communication with new state
           
    
  }
}

#pragma vector=USI_VECTOR
__interrupt void USI_ISR(void)
{
  SET_BUSY_FLAG();          // set busy flag - slave is ready with a new communication
  NextState = USISRL;       // read new command
  USICNT = 8;               // Load bit counter for next TX
  _BIC_SR_IRQ(LPM4_bits);   // Exit from LPM4 on RETI
  RESET_BUSY_FLAG();        // clears busy flag - ready for new communication
}


