#include <iostream>


using namespace std; 

class rectangleEX {

	friend ostream& operator<<(ostream&, const rectangleEX&);
	friend rectangleEX operator*(const rectangleEX &, const rectangleEX &);
	friend rectangleEX operator/(const rectangleEX &, const rectangleEX &);
public:
	rectangleEX();
	rectangleEX(double l, double w);
	void setDimension(double l, double w);
	double getLength() const;
	double getWidth() const;
	double area() const;
	double perimeter() const;

	rectangleEX operator+(const rectangleEX &) const;
	rectangleEX operator-(const rectangleEX &) const;

	rectangleEX operator++();
	rectangleEX operator++(int); //post decrement determined by the int argument


private:
	double length;
	double width;
	
}; 