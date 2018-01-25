//
// triangle.h
//
// Triangle class models triangle with side lengths a, b, c
//
// Use the contents of this file to implement triangle.cpp
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//

#include "shape.h"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle : public Shape
{
 private:
	double a, b, c;        	// Side lengths

 public:
	Triangle();                               	// Initializes a, b, c to 0.0 and red, green, blue to 0

	Triangle(double aaa, double bbb, double ccc,  // Initializes a, b, c to aaa, bbb, ccc and
         	int rr, int gg, int bb);         	// red, green, blue to rr, gg, bb respectively
                                            	 

	double area() const;                      	// Returns area value computed from a, b, c
};

#endif

