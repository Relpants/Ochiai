//
// color.h
//
// Color class models the color of an item <red,green,blue>
//
// Use the contents of this file to implement color.cpp
//
// DO NOT MODIFY OR SUBMIT THIS FILE
//

#include <iostream>
using namespace std;

#ifndef COLOR_H
#define COLOR_H

class Color
{
  private:
	int 	red;        	// Amount of red 0-255
	int 	green;      	// Amount of green 0-255
	int 	blue;       	// Amount of blue 0-255

  public:
	Color();            	// Initializes red, green, and blue to zero
	void setRed(int rr);	// Sets red to rr
	void setGreen(int gg);  // Sets green to gg
	void setBlue(int bb);   // Sets blue to bb

	int getRed() const; 	// Returns red
	int getGreen() const;   // Returns green
	int getBlue() const;	// Returns blue

	void print() const  	// Writes <red,green,blue> to std output
	{
    cout << "<" << getRed() << "," << getGreen() << "," << getBlue() << ">";
	}
};

#endif

