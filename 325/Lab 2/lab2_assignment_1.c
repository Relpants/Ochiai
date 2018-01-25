/*---------------------------------------------
* Dan Aldridge
* Lab 2 assignment: 1
* Friday lab session 3:50-6:50
* 8/21/16
* Lee Seemann
* This program returns the size,min, and max value of the following data types
char,short,int,long,u_int,u_long,float, and double
* Using float.h and limits.h libraries this program pulls keywords from respective
libraries. It uses these keywords in print statements to print the desired values to screen
*-------------------------------------------------*/



#include <limits.h>
#include <float.h>
#include <stdio.h>

int main (void)
{
    
    printf("Size of char: %d \n", sizeof(char));                            // return size of char
    printf("Min and max value of char: %d , %d \n,\n", CHAR_MIN, CHAR_MAX); // return min and max value for char
   
    printf("Size of short: %d \n", sizeof(short));                          // return size of short
    printf("Min and max value of short: %d, %d \n,\n", SHRT_MIN, SHRT_MAX); // return min and max value for short
    
    printf("Size of int: %d \n", sizeof(int));                              // return size of int
    printf("Min and max value of int: %d, %d \n,\n", INT_MIN, INT_MAX);     // return min and max value for int
    
    printf("Size of long: %ld \n", sizeof(long));                           // return size of long
    printf("Min and max value of long: %ld, %d \n,\n", LONG_MIN, LONG_MAX); // return min and max value for long
    
    printf("Size of unsigned int: %u \n", sizeof(unsigned int));            // return size of u_int
    printf("Min and Max value of unsigned int: 0, %u \n,\n", UINT_MAX);     // return min and max value for u_int
    
    printf("Size of unsigned long: %u \n", sizeof(unsigned long));          // return size of u_long
    printf("Min and Max value of unsigned long: 0, %u \n,\n", ULONG_MAX);   // return min and max value for u_long
    
    printf("Size of float: %d \n", sizeof(float));                          // return size of float
    printf("Min and Max value of float: %e, %e \n,\n"   , FLT_MIN, FLT_MAX);// return min and max value for float
   
    printf("Size of double: %d \n", sizeof(double));                        // return size of double
    printf("Min and Max value of double: %e, %e \n,\n", DBL_MIN, DBL_MAX);  // return min and max value for double
    
    
    
    return 0;
    
}