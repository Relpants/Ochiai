//
// rectangle.h
//
// Rectangle class models Rectangle with side lengths l, w
//
// Use the contents of this file to implement rectangle.cpp
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//

#include "shape.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Shape
{
 private:
	double l, w;                              	// Side lengths

 public:
	Rectangle();                              	// Initializes l, w to 0.0 and red, green, blue to 0

	Rectangle(double ll, double ww,           	// Initializes l, w to ll, ww and
          	int rr, int gg, int bb);        	// red, green, blue to rr, gg, bb respectively
                                            	 

	double area() const;                      	// Returns area value computed from l, w
};

