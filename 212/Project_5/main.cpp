//
// main.cpp
//
// Driver program which is used to test each
// class member function.
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <typeinfo>
#include "color.h"
#include "shape.h"
#include "triangle.h"
#include "rectangle.h"

using namespace std;                 	// Global using declaration

// Prototypes for support functions -- definitions appear after main()
void Bar(int n);                     	// Prototype for Bar function
void Print(Shape*  someShape);       	// Prototype for Print function
//void PrintColor(Color someColor);    	// Prototype for PrintColor function



// Start of main() function

int main (int argc, char* const argv[])  // Command-line arguments (more on this later)
{
  ifstream inputs;   				  	// Input file stream variable for test file
  char op, ch;   						  // Hold operation and optional char input from test file
  Shape* ptr = NULL;                 	// Pointer to abstract shape object
  string operand1,operand2,operand3,operand4;   // Holds operand values input from test file
  string comment;                    	// Holds comment input from test file
  Color someColor;                   	// Holds color input from file
  char t;                            	// Holds s for Shape, t/T for Triangle, r/R for Rectangle
  double a, b, c;                    	// Holds lengths a, b, c input from file
  int red, green, blue;              	// Holds red, green, blue input from file
  Color* color;

 
  // Output usage message if test input file name is not provided
  if (argc != 2)
  {
	cout << "Usage:\n  project02  <inputfile>\n";
    return 1;
  }
 
  // Attempt to open test input file -- terminate if file does not open
  inputs.open(argv[1]);
  if (!inputs)
  {
	cout << "Error - unable to open input file" << endl;
    return 1;
  }

  Bar(60);                                       	// Output long bar

  // Process comment line from input file
  getline(inputs, comment);                      	// Input file header comment
  cout << endl << comment << endl << endl;       	// Output file header comment

  // Configure floating point decimal output
  cout << fixed << showpoint << setprecision(2);
    
    
  // Below is the primary loop that processes each operation appearing within the test file.
  // Starts with an initial priming read of first operation
 
  inputs >> op;   			                      	// Attempt to input first test operation from file
    
  while (inputs)                                 	// While Not-EOF
  {
	switch (op)                                  	// Process operation input from test file
	{
 	case '#':   // Test file comment
        	getline(inputs, comment);  	// Input and echo the comment appearing in the test file
        	cout << '#' << comment << endl;
        	break;
    
 	case '?':   // Print Operator
        	Print(ptr);
        	break;    

 	case '~':   // Print Bar
        	Bar(40);                     	// Output short bar
        	break;   			 

 	case '+':   // Use symbol input from file to invoke appropriate constructor
             	inputs >> t;           	// Input object type symbol

             	try
             	{
               	cout << "Constructor -- ";
               	switch (t)
               	{
                 	case 's':  // Shape default constructor
                            	cout << "Shape() ";
                            	ptr = new Shape();
                            	break;

                 	case 'S':  // Shape parameterized constructor
                            	inputs >> red >> green >> blue;
                            	cout << "Shape(" << red << "," << green << "," << blue << ") ";
                            	ptr = new Shape(red,green,blue);
                            	break;

                 	case 't':  // Triangle default constructor
                            	cout << "Triangle() ";
                            	ptr = new Triangle;
                            	break;

                 	case 'T':  // Triangle parameterized constructor
                            	inputs >> a >> b >> c >> red >> green >> blue;
                            	cout << "Triangle(" << a << ", " << b << ", "
                                 	<< c << ", " << red << ", " << green << ", " << blue << ") ";
                            	ptr = new Triangle(a, b, c, red, green, blue);
                            	break;

                 	case 'r':  // Rectangle default constructor
                            	cout << "Rectangle() ";
                            	ptr = new Rectangle;
                            	break;

                 	case 'R':  // Rectangle parameterized constructor
                            	inputs >> a >> b >> red >> green >> blue;
                            	cout << "Rectangle(" << a << ", " << b << ", "
                                	<< red << ", " << green << ", " << blue << ") ";
                            	ptr = new Rectangle(a, b, red, green, blue);
                            	break;

                 	default:   cout << "Error: unrecognized object" << endl;
                	} // End switch (op)


                	cout << "Completed";
              	}  // End try
              	catch ( ... )                    	// Catch any exception thrown above
              	{
                	cout << "Failed";  
              	}
   		 
              	cout << endl;             	 
              	break;

  	case 'c':   // getColor()
              	cout << "getColor() -- ";
              	try
              	{
                	ptr->getColor().print();
                	cout << "  Completed";
              	}
              	catch ( ... )
              	{
                	cout << "Failed";
              	}
              	cout << endl;
              	break;

  	case 'a':   // area(...)
              	inputs >> operand1;
              	cout << "area() -- ";
              	try
              	{
                	cout << ptr->area();
              	}
              	catch ( ... )
              	{
                	cout << "Failed";
              	}
              	cout << endl << endl;
              	break;    
   					   
  	case '-':   // Destructor
              	try
              	{
                	cout << "Destructor -- ";
                	delete ptr;                    	// Deallocate currency
                	cout << "Completed";
   		        	ptr = NULL;                 	// Make sure that ptr is not a dangling pointer
              	}
              	catch ( ... )
              	{
                	cout << "Failed";
              	}
              	cout << endl << endl;
              	break;   	 

  	default:	// Error
              	cout << "Error - unrecognized operation '" << op << "'" << endl;
              	cout << "Terminating now..." << endl;
              	return 1;
              	break;
	}
      
	inputs >> op;                                 	// Attempt to input next command
  }
 
  cout << endl;
  Bar(60);                                       	// Output long bar
 
  return 0;
}

/************** Implementation of Print() and Bar() functions ********************/

// DO NOT MODIFY THIS CODE

void Bar(int n)
// Bar() -- prints horizontal bar
{
    for(int k = 0; k < n; k++)
    	cout << '#';
	cout << endl;
}  // End Bar()


void Print(Shape*  someShape)
// Writes shape description stdout
{
   string s = typeid(*someShape).name();
   cout << s << endl;      	 
}

/**************  End of main.cpp  ***************/



 
