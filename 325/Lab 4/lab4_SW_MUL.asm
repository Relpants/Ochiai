* Dan Aldridge
* Lab 4 assignment: 1, SW_MUL
* 9/5/16
* Lee Seemann
* Subroutine that multiplies two integers, using stack method
* Input    : 2 Registers are pushed to stack R12,R13
              R12 -- Register to temp. hold first operand
              R13 -- Register to temp. hold 2nd operand
              R14 -- Result of multiplication will be moved to here
* Output   : No output 
*--------------------------------------------------------------------------------*/
#include "msp430.h"                     ; #define controlled include file

        PUBLIC SW_MUL
        
        RSEG CODE

SW_MUL:  
        PUSH    R12                     ; push register to hold 2nd operand. to stack
        PUSH    R13                     ; push register to hold first operand. to stack 
        CLR     R12                     ; clear register 
        CLR     R13                     ; clear register 
        CLR     R14                     ; clear register, "result" register
        MOV     6(SP), R12              ; move the sp to point to the 2nd operand then move that operand into R12
        MOV     8(SP), R13              ; move the sp to point to the first operand then move that operand into R13
        
jnext:  ADD R12, R14                    ; add the contents of R12 into R14
        DEC R13                         ; decrement 1 from R13
        CMP #0, R13                     ; compare 0 to R13
        JEQ jend                        ; jump to jend if 0 and R13 are ==
        JMP jnext                       ; if R13 is not equal to 0 jmp back to jnext 


jend:  
        POP     R13                     ; pop R13 off stack
        POP     R12                     ; pop R12 off stack
        
        RET                             ; return to main program
        


        END
