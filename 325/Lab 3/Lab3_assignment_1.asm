/*-------------------------------------------------------------------
* Dan Aldridge
* Lab 3 assignment: 1
* Friday Lab session 3:55-6:50
* 8/21/16
* Lee Seemann
* This program takes a string and counts the number of uppercase,lowercase, and # of overall
characters in the string, "printing out" uppercase in port 1, lowercase in port 2 and storing the num
of characters in R6
*Using the ASCII table we compare each character in the string, first if the char is null then 
its the end of the string and we jump to end, next we check it is a character with a val
less than uppercase letter ASCII values, if so count as a character, we do this for lower case 
aswell, In summary checking if it is an ASCII character in the range of uppercase letters,
lower case, or just an non letter ASCII character. We increment the appropriate counter
depending on which case it falls in
*---------------------------------------------------------------------*/

#include "msp430.h"                                     ; #define controlled include file

        ORG 0FF00h
myStr   DB "Welcome to CPE325, home of the MSP430!"     ; create string named myStr, placed on stack


        NAME    main                                    ; module name
        
        
        PUBLIC  main                                    ; make label visible
        
        ORG     0FFFEh
        DC16    init                                    ; set reset vector to label init
        
        RSEG    CSTACK                                  ; predec. of segment
        RSEG    CODE                                    ; place program in CODE seg.
        
        
init:   MOV     #SFE(CSTACK), SP                        ; set up stack
        
main:   NOP                                             ; main program
        BIS.B   #0FFh,&P1DIR                            ; configure P1.x output
        BIS.B   #0FFh,&P2DIR                            ; configure P2.x output
        MOV.W   #myStr, R4                              ; load the starting address of the string "myStr" into R4
        
        CLR.B   R6                                      ; clear total character counter
        CLR.B   R7                                      ; clear uppercase counter
        CLR.B   R8                                      ; clear lowercase counter
                
        MOV.B   #'`', R9                                ; load ASCII char ` into R9
        MOV.B   #'@', R10                               ; load ASCII char @ into R10
          
jnext:  MOV.B   @R4+, R5                                ; get next character in string
        CMP     #0,R5                                   ; is this a null character
        JEQ     lend                                            ; if so jump to end
        CMP.B   R5, R10                                ; compare the character to R10 which is ASCII VAL  @ ---  64 decimal
        JGE     jcount                                          ; if R5 <= R10 in terms of ASCII vals jump to jcount *meaning this val has an ASCII val outside uppercase or lowercase ranges*
        CMP.B   #'[', R5                                ; compare the character to ASCII VAL [ ---- 91 decimal
        JGE     jlower                                          ; if it is >= to 91 then jump to jlower * this could be a lowercase char*
        JMP     jupper                                  ; if it hits this jmp then it is an uppercase char
        
        
        
jupper: INC     R7                                      ; uppercase segment, increment the uppercase counter
        INC     R6                                      ; an uppercase is a character so also increment the total char counter
        JMP     jnext                                   ; jmp to jnext, getting the next character in the string
 
 
jlower: CMP.B   R5, R9                                  ; lowercase segment, additional checking, compare the character to R9 which is ASCII val ` --- 96
        JGE     jcount                                          ; if R5 <= R9 in terms of ASCII vals jump to jcount *meaning this val has an ASCII val outside uppercase or lowercase ranges* 
        CMP.B   #'{', R5                                ; compare to ASCII val { --- 122  
        JGE     jcount                                          ; jmp to count, this character has a greater ASCII Val than both uppercase and lowercase
        INC     R8                                      ; if it hits this point then it is a lowercase char, so increment lowercase counter
        INC     R6                                      ; since lowercase is a also increment the total char counter
        JMP     jnext                                   ; jmp to jnext, to get next character in the string
   
   
jcount: INC     R6                                      ; increment total char counter
        JMP     jnext                                   ; jmp to jnext, to get next character in the string
          
          
          
         
          
          
lend:   MOV.B   R7, &P1OUT                              ; set all P1 pins
        MOV.B   R8, &P2OUT                              ; set all P2 pins
        BIS.W   #LPM4, SR                               ; LPM4
        NOP
        
        
        END
