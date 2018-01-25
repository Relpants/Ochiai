#include <iostream>

#include "triangle.h"

using namespace std;

Triangle::Triangle() : Shape()
{
    a = 0.0;
    b = 0.0;
    c = 0.0;
}
Triangle::Triangle(double aaa, double bbb, double ccc, int rr, int gg, int bb) : Shape (rr, gg, bb)
{
    a = aaa;
    b = bbb;
    c = ccc;
    
}  
double Triangle::area() const
{
    return ((a + b + c)/2);
}


