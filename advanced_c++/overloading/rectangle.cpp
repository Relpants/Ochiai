#include "rectangle.h"



rectangleEX::rectangleEX(){
	length = 0;
	width = 0;
}
rectangleEX::rectangleEX(double l, double w){
	length = l;
	width = w;
}

ostream& operator<<(ostream& osObject, const rectangleEX& rectangle){

	if(rectangle.length != 0 && rectangle.width != 0)
		osObject << "length = " << rectangle.length << ", width = " << rectangle.width;
	else
		osObject << "Rectangle not initalized with valid length and width";	
	return osObject;
}
rectangleEX operator*(const rectangleEX& rec1, const rectangleEX& rec2){

	rectangleEX tmprectangle;

	tmprectangle.length = rec1.length * rec2.length;
	tmprectangle.width	= rec1.width * rec2.width;
	
	return tmprectangle;
}

rectangleEX operator/(const rectangleEX& rec1, const rectangleEX& rec2){

	rectangleEX tmprectangle;

	tmprectangle.length = rec1.length / rec2.length;
	tmprectangle.width	= rec1.width / rec2.width;
	
	return tmprectangle;
}
void rectangleEX::setDimension(double l, double w){

	length = l;
	width = w;
}

rectangleEX rectangleEX::operator+(const rectangleEX& rectangle) const{

	rectangleEX tmp;

	tmp.length = length + rectangle.length;
	tmp.width = width + rectangle.width;

	return tmp;
}

rectangleEX rectangleEX::operator-(const rectangleEX& rectangle) const{

	rectangleEX tmp;

	tmp.length = length - rectangle.length;
	tmp.width = width - rectangle.width;
}