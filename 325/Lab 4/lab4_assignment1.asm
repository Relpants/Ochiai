/*---------------------------------------------------------------------------
* Dan Aldridge
* Lab 4 assignment: 1
* 9/5/16
* Lee Seemann
* This program uses external files or "functions" to compute multiplication using a stack and hardware method
* Using the hardware method first we take two 16bit signed integers and commit multiplication 
in two steps using the designated multiplier registers MPYS and OP2 this is then stored in RESLO 
register to later be moved into R15. Next a stack method is used to multiply two numbers where you push the two 
numbers to the stack, then push the registers, the SP is used to place the numbers in the corresponding registers
commit multiplication through "addition".Pop registers off stack, the result will be stored in R14.
*------------------------------------------------------------------------------*/
#include "msp430.h"                     ; #define controlled include file

        ORG 0FF00h

        NAME    main                    ; module name
        PUBLIC  main                    ; make the main label visible
 
        ORG     0FFFEh
        DC16    init                    ; set reset vector to 'init' label

        RSEG    CSTACK                  ; pre-declaration of segment
        RSEG    CODE                    ; place program in 'CODE' segment
        
        EXTERN SW_MUL                   ; external file or "function" to perform software multiplication
        EXTERN HW_MUL                   ; external file or "function" to perform hardware multiplication
        
        CLR.B     R14                     ; clear register that will serve as software multiplication result
        CLR.B     R15                     ; clear register that will serve as hardware multiplication result


init:   MOV     #SFE(CSTACK), SP        ; set up stack

main:   NOP                             ; main program
       
        CALL    #HW_MUL                 ; call of the hardware "file or function" to calculate multiplication using the mult. registers
        
        PUSH   #5                       ; push the number 5 to the stack(first operand)
        PUSH   #6                       ; push the number 6 to the stack(2nd operand)
        CALL   #SW_MUL                  ; call the software "file or function" to calculate mult. using the stack method
        ADD    #4, SP                   ; collapse stack
        
        BIS.W   #LPM4, SR               ; LPM4
        NOP

        

        


        END
        
        
        
        
        
        
        
        
        
    /* CLOCK COUNTERS      HW_MUL = 20    SW_MUL = 68
