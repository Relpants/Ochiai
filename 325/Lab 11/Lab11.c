//******************************************************************************
//   MSP430xG461x Demo - DAC12_0, Output Voltage SINEWAVE on DAC0
//   Device: TI Experimeter's Board
//
//   Description: Using DAC12_0 and 2.5V ADC12REF reference with a gain of 1,
//   output sinisoidal wave on P6.6, y=1.25(1+sin(x)).
//   Normal mode is LPM0 with CPU off.  WDT used
//   to provide ~0.064ms interrupt used to wake up the CPU and update the DAC
//   with software. Use internal 2.5V Vref.
//   ACLK = 32kHz, SMCLK = MCLK = WDTCLK = default DCO 1048576Hz
//
//
//                MSP430xG461x
//             -----------------
//         /|\|              XIN|-
//          | |                 | 32kHz
//          --|RST          XOUT|-
//            |                 |
//            |        DAC0/P6.6|--> sine (10Hz)
//            |                 |
//
// Authors: Aleksandar Milenkovic, milenkovic@computer.org
//          Max Avula, ma0004@uah.edu
//			UAHuntsville
// Date:  March 2012
// Built with IAR Embedded Workbench IDE Version: 6.3.11.2079
//******************************************************************************
#include "msp430xG46x.h"


#include "sine.h"  
#include "triangle.h"
#include "square.h"

#define SW1 BIT0&P1IN
#define SW2 BIT1&P1IN

void main(void) {
  unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;                   // Stop WDT
  ADC12CTL0 = REF2_5V + REFON;                // Internal 2.5V ref on
  //for (i=50000; i>0; i--);                    // Delay to allow Ref to settle
  DAC12_0CTL = DAC12IR + DAC12AMP_5 + DAC12ENC;   //Sets DAC12
  CCTL0 = CCIE;                                // CCR0 interrupt enabled
                                    // Sets Timer Freq (1048576*0.1sec/256)
  
  P1DIR |=  0x00;
  P1OUT |= 0x00;
  
  
  FLL_CTL0 |= XCAP18PF;
  SCFI0 |= FN_2;
  SCFQCTL |= 61;
  CCR0 = ((4000000/25)/256); 
  TACTL = TASSEL_2 + MC_1;                     // set clock to SMCLK, up mode
  i=0;
  while (1)
  {
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, interrupts enabled
    
    while((SW1)==0)
    {
      DAC12_0DAT = sine[i];
      DAC12_0DAT &= 0xFFF;
      i=(i+1)%256;
      while((SW2)==0)
      {
        DAC12_0DAT = triangle[i];
        DAC12_0DAT &= 0xFFF;
        i=(i+1)%256;
      }
      
    }
    while((SW2)==0)
    {
      DAC12_0DAT = square[i];
      DAC12_0DAT &= 0xFFF;
      i=(i+1)%256;
      while((SW1)==0)
      {
          DAC12_0DAT = triangle[i];
          DAC12_0DAT &= 0xFFF;
          i=(i+1)%256;
      }
    }
    
    
    
  }
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TA0_ISR(void)
{
  __bic_SR_register_on_exit(LPM0_bits);     // Exit LPMx, interrupts enabled
}
