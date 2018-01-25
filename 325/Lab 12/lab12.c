

/*-------------------------------------------------------------------
* Dan Aldridge
* Lab 12 assignment: 1
* Friday Lab session 3:55-6:50
* 11/7/16
* Lee Seemann
* Use the 4168's on board temperature sensor to display via hyperterm. wirelessly. 
* Using UART communication we calculate the temperature in F and C, these values 
come from the onboard sensor in the msp430. These values are calculated using formulas
and then sent 1 bit at time to to hyperterm to display the correct values. This
program was first tested using a serial connection and then later a wireless communicate
as was required for our assignment.
*---------------------------------------------------------------------*/
#include <msp430xG46x.h> 
#include  <stdio.h>

#define SW1 (BIT0&P1IN)
#define SW2 (BIT1&P1IN)

unsigned char thr_char;  /* hold char from UART RX*/
unsigned char rx_flag; 
char message[] = "Press SW1 for Fahrenheit, Press SW2 for Celsius"; // display msg
int i; 

long int IntDegF=0;     // faren. value
long int IntDegC=0;     // celsius value
long int temp;          
char NewKey[25];       // temp array to display values in hyperterm




// UART Initializaion
void UART_Initialize(void);     
//send char function
void UART_putchar(char c);


void UART_Initialize(void)
{
  P2SEL |= BIT4 ;                // P2.4  USCI_A0 TXD
  UCA0CTL1 |= UCSSEL_2;          // SMCLK
  UCA0BR0 = 0x09;                // 1MHz/115200   (lower byte)
  UCA0BR1 = 0x00;               // 1MHz/115200   (upper byte)
  UCA0MCTL = 0x02;              // Modulation (UCBRS0=0x01)(UCOS16=0)
  UCA0CTL1 &= ~UCSWRST;
  IE2 |= UCA0RXIE;
}  


void UART_putchar(char c) {
  // wait for other character to transmit
  while (!(IFG2 & UCA0TXIFG));
  UCA0TXBUF = c;
}

void faren(){
  
  IntDegF = (temp - 2519) * 761;        //faren calculation
  IntDegF = IntDegF / 4096;
  
  sprintf(NewKey, "T(F)=%ld\n", IntDegF);       //read in the new faren value
  for(i = 0; i < 25; i++) {             // one bit at a time 
         thr_char = NewKey[i];               // using newkey array
         UART_putchar(thr_char);        // display to hyperterm
          }
    
}

void cels(){
  
  IntDegC = (temp - 2692) * 423;        //celsius calc
  IntDegC = IntDegC / 4096;
  
  sprintf(NewKey, "T(C)=%ld\n",IntDegC); //read in the new celsius value
  for(i = 0; i < 25; i++) {                     // one bit at a time
         thr_char = NewKey[i];          // using newkey array
         UART_putchar(thr_char);                // display to hyperterm
          }
 
}

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           // Stop watchdog timer
    
    ADC12CTL0 = SHT0_8 + REFON + ADC12ON;
    ADC12CTL1 = SHP;                      // enable sample timer
    ADC12MCTL0 = 0x01A;
    ADC12IE = 0x001;
    P1DIR &= ~0x03;
    rx_flag = 0;            // rx default state "empty"
    _EINT();                // enable global interrupts
    
  
    UART_Initialize();          // call uart function
    
    for(i = 0; i < 48; i++)           // display greeting msg
    {
	thr_char = message[i];
	UART_putchar(thr_char);
        
    }
    UART_putchar('\n');    // newline
    UART_putchar('\r');    // carriage return
    while(1){  
    if(SW1==0)
    {   ADC12CTL0 |= ENC + ADC12SC;         // Sampling and conversion start
        _BIS_SR(CPUOFF + GIE);              // LPM0 with interrupts enabled
        faren();
        UART_putchar('\n');    // newline
        UART_putchar('\r');    // carriage return
        for(int i = 0; i < 10000; i++);         //delay
    }
    if(SW2==0)
    {
         ADC12CTL0 |= ENC + ADC12SC;         // Sampling and conversion start
         _BIS_SR(CPUOFF + GIE);              // LPM0 with interrupts enabled
         cels();
         UART_putchar('\n');    // newline
         UART_putchar('\r');    // carriage return
         for(int i = 0; i < 10000; i++);        //delay
    }
    
   }
}
#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
    temp = ADC12MEM0;                   // Move results, IFG is cleared
    _BIC_SR_IRQ(CPUOFF);                // Clear CPUOFF bit from 0(SR)
}

