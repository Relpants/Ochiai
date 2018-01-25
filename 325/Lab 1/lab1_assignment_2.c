
/*---------------------------------------------
* Dan Aldridge
* Lab 1 assignment: 2
* Friday lab session 3:50-6:50
* 8/22/16
* Lee Seemann
* This program calculates the number of uppercase values in a string
* Using a for loop a counter will be incremented everytime the function isupper is true
*-------------------------------------------------*/



#include <stdio.h>
#include <ctype.h>
int main(void)
{
  int c = 0;                                    //counter
  char message[100] = "I like StarWars";        //string
  
  for(int i = 0; i <= 100; i++)                 //for loop that will increment if isupper is true on each element in string
  {
    if( isupper(message[i]))                    //checks to see if element is an uppercase letter
    {   
      c++;                                      //increments if it is an uppercase letter
    }
        
  }
        
        
 printf("%s : has %d number of cap letters", message,c);        //prints message and its number of uppercase letters
        
    
    return 0;
}