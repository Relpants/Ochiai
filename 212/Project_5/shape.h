#include <iostream>

#include "color.h"

using namespace std;

#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
  private:
   Color c;

  public:
	Shape();
	Shape(int r, int g, int b);
	Color getColor() const;
	double area() const;

};

#endif
