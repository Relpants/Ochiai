/*------------------------------------------------------------------------------
* Dan Aldridge
* Lab 4 assignment: 1, HW_MUL
* 9/5/16
* Lee Seemann
* Subroutine that multiplies two integers
* Input    : Dedicated Mult. Registers MPYS, OP2, RESLO will be used
              MPYS -- 1st number will be moved to this register.
              OP2 -- 2nd number will be placed here , when this command executes the mult. will be done
              RESLO -- Result of multiplication will be stored here 
              R15 -- Result of multiplication will be moved to here
* Output   : No output 
*------------------------------------------------------------------------------*/
#include "msp430.h"                     ; #define controlled include file	

        PUBLIC HW_MUL

	RSEG CODE

HW_MUL:
        MOV     #4, &MPYS               ; Load first operand
        MOV     #5, &OP2                ; Load 2nd operand
        MOV     RESLO, R15              ; Move result from mult. to R15
        RET                             ; return to main program
        
        
        END
