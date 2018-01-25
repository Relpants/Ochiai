//
// shape.cpp
//
// Shape class models a generic geometric shape with color
// defined by a private Color object attribute c
//
// Use the contents of this file to reverse engineer the contents of shape.h
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//
//

#include "shape.h"

Shape::Shape()
// Initializes c to <0,0,0>
{
	c = Color();           	 
}

Shape::Shape(int r, int g, int b)
// Initializes c to <r,g,b>
{
	c.setRed(r);
	c.setGreen(g);
	c.setBlue(b);
}

Color Shape::getColor() const
// Returns color of object
{
	return c;
}

double Shape::area() const
// Returns default area of 0.0 -- polymorphic function
{
	return 0.0;
}

