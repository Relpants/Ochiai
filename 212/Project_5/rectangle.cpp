#include <iostream>


#include "shape.h"
#include "rectangle.h"

using namespace std;

Rectangle::Rectangle() : Shape()
{
    l = 0.0;
    w = 0.0;
}
Rectangle::Rectangle(double ll, double ww, int rr, int gg, int bb) : Shape (rr, gg, bb)
{
    l = ll;
    w = ww;
}
double Rectangle::area() const
{
    return l*w;
    
}