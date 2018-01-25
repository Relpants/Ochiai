
/*---------------------------------------------
* Dan Aldridge
* Lab 1 assignment: 1
* Friday lab session 3:50-6:50
* 8/22/16
* Lee Seemann
* This program calculates a number raised to a power
* Using a for loop a var=1 will be multiplied by the base n or "pow" times
*-------------------------------------------------*/

#include <stdio.h>
int main(void)
{
  int base = 2; //Declare the base 
  int pow = 5; //Declare the power
  int final = 1; //Var that will hold the final value
  
  for(int t = 1 ;t <= pow; t++) //for loop that iterates till t is <= pow
  {
    final = final*base;         //each iteration the total is multiplied by the base and will be done t times or "pow" times
  }
  
  printf(": %d" , final);       //print the final value 
  return 0;
}






// With non recursion my clock cycle for 
// the whole program was: 84


//The recursion program resulted in a 
// clock cycle of : 125


// I believe the recursion program had a higher clock cycle 
// because there are more instructions when another function 
// calls itself resulting in longer clock cycle