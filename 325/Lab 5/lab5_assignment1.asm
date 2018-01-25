/*-------------------------------------------------------------------
* Dan Aldridge
* Lab 5 assignment: 1
* Friday Lab session 3:55-6:50
* 9/12/16
* Lee Seemann
* This program is the introduction to the MSP430, it starts with both LEDs On, 
then if SW1 pressed turn both LEDs off, if SW2 pressed toggle LED1 and LED2
*Using Both P2.2 + P2.1 for both LEDs, and P1.1 and P1.0 for the switches.
We use switches to determine what happens to the LEDs depending on which is 
pressed. Interrupts are enabled and are designed to break to certain seg. of codes
if these switches are pressed allowing us to "live" in an infin
*---------------------------------------------------------------------*/

#include <msp430xG46x.h>

RSEG            CSTACK                  ; Define stack seg.
RSEG            CODE                    ; Assemble to Flash Mem.

RESET:          
        mov     #SFE(CSTACK), SP        ; Initialize Stack ptr

STOPWDT:
        mov.w   #WDTPW + WDTHOLD, &WDTCTL       ; Stop WatchDog Timer

SETUP:
        bis.b   #006h, &P2DIR           ; Set P2.2 & P2.1 to output (0000_0110)
        bis.b   #006h, &P2OUT           ; Set P2OUT to 0000_0110 turning LED1&LED2 ON
        
        nop
        
        bis.w   #GIE,   SR              ; Enable global interrupts
        
        bis.b   #001h,  &P1IE           ; Enable Port 1 interrupt from bit 0
        bis.b   #001h,  &P1IES          ; Set interrupt for hi to low edge
        bic.b   #001h,  &P1IFG          ; Clear interrupt flag
        
        
        bis.b   #002h,  &P1IE           ; Enable Port 1 interrupt from bit 1
        bis.b   #002h,  &P1IES          ; Set interrupt for hi to low edge
        bic.b   #002h,  &P1IFG          ; Clear interrupt flag
        
        
        
        
INFL:                                   
       ; jmp     $                       ; loop until intterupt
        
        
SW1_ISR:                                
        bic.b   #001h,  &P1IFG          ; Clear switch 1 interrupt flag
        bic.b   #002h,  &P1IFG          ; Clear switch 2 interrupt flag
        
                  
Debounce:
        mov.w   #02000, R15             ; set to (2000 * 10 ms delay)
        
L1:                                     
        dec.w   R15                     ; Decrement R15
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        jnz     L1                      ; Check if Delay over
        bit.b   #00000001b,     &P1IN   ; verify SW1 is still pressed
        jnz     SW_CHECKER              ; IF SW1 is NOT pressed, CHECK SW2
        jmp     LEDoff                  ; IF SW1 is pressed, turn off LEDs
        
        
        
SW_CHECKER:
        bit.b   #00000010b,     &P1IN   ; verify SW2 is still pressed
        jnz     isr_ret                 ; if not, wait for SW2 pressed
        jmp     SW2wait                 ; if so, jump to SW2wait 
        
        
LEDoff:
        bic.b   #006h,          &P2OUT  ; Turn off LED1&LED2
        
SW1wait:
        bit.b   #001h,          &P1IN   ; Check Sw1
        jz      SW1wait                 ; wait until Sw1 is released
        bis.b   #006h,          &P2OUT  ; turn on LED1&LED2
        jmp     isr_ret
        
SW2wait:
        bit.b   #002h,          &P1IN   ; Check Sw2
        jnz     isr_ret                 ; wait until Sw2 is released
MainLoop:
        xor.b   #006h,          &P2OUT  ; "Alt Toggle" LED1&LED2
        mov.w   #025000,R14             ; Delay
L2:
        dec.w   R14                     ; Decrement R14
        nop
        nop
        nop
        nop
        nop
        nop
        jnz     L2
        jmp     SW2wait
isr_ret:
        bis.b   #006h,          &P2OUT  ; Turn on Both LEDs
        reti                            ; return from interrupt
        
        
        COMMON  INTVEC                  ; interrupt Vectors
        
        ORG     RESET_VECTOR            ; MSP430 RESET Vectors
        DW      RESET   
        ORG     PORT1_VECTOR            ; Port1 interrupt vector
        
        DW      SW1_ISR                 ; go to Sw1_ISR
        
        END






