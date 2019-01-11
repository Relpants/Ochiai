// static members example

#include <iostream>
using namespace std;

class example {
	public:
	  static int count;    //static members must only have its prototype in the class
	  example () { count++; }
	  ~example () { count--; }

};

int example::count=0;	//static member definition

int main () {
	example a;
	example b[5];

	example * c = new example;

	cout << a.count << endl;	// prints 7, because we have 7 objects

	cout << b[0].count << endl; 

	delete c;				// delete one of the objects

	cout << a.count << endl;	// now we have 6 because count is shared between all objects

	cout << example::count << endl; // can also refer to it directly since its static and only 1 "copy" exists

	return 0;
}