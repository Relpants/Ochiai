/*---------------------------------------------
* Dan Aldridge
* Lab 2 assignment: 2
* Friday lab session 3:50-6:50
* 8/21/16
* Lee Seemann
* This program creates an integer array, then takes a scalar and multiples each value
by that scalar
* Two for loops are used in this program to multiply an array by a scalar, the first
is used for array traversal for multiplcation, the 2nd is then used to print out the
new array to the screen
*-------------------------------------------------*/



#include <stdio.h>
int main (void)
{
    int a[] = {1,2,3,4,5};              //create an array of 5 integer values
    
    for(int i = 0; i < 5; i++)          //using a loop traverse each value and multiply by scalar
    {
        a[i] *= 5;                      //multiply by scalar
    }
    
    for(int x = 0; x < 5; x++)          //a 2nd loop will be used to print out the new scalar
    {
         printf(" %d", a[x]);           //print to term
    }
    
    return 0;
    
}
