#include <iostream>
#include "rectangle.h"


using namespace std;

int main(){
	rectangleEX rec1(3,4);
	rectangleEX rec2(4,5);



	cout << "(ostream operator) Line 13: rectangle1: " << rec1 << std::endl;
	cout << "(ostream operator) Line 14: rectangle2: " << rec2 << std::endl;

	cout << "(ostream operator and addition operator) Line 16: addition: " << rec1 + rec2 << std::endl;

	return 0;


}