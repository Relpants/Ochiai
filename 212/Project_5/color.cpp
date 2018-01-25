#include <iostream>

#include "color.h"


using namespace std;


Color::Color()
{
    red = 0;
    green = 0;
    blue = 0;

}
void Color::setRed(int rr)
{
    red = rr;
}
void Color::setGreen(int gg)
{
    green = gg;
}
void Color::setBlue(int bb)
{
    blue = bb;
}
int Color::getRed() const
{
    return red;    
}
int Color::getGreen() const
{
    return green;
}
int Color::getBlue() const
{    
    return blue;
}


