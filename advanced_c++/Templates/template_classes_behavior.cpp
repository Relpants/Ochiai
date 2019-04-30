
#include <iostream>
using namespace std;

template <class T> // declaring the class as a template 
class mypair {			
	T a, b;	// declaring two variables of type T where T is the passed in type to the class
	public:
	  mypair (T first, T second){ a = first; b = second;}	//basic constructor
	  														// takes arguments of type "T"
	  T getmax();		// declaring a 
};

template <class T>		// declaring the function as a template
T mypair<T>::getmax(){		// T declares what type the function is
	T retval;			// T declares what type of variable
	retval = a>b? a : b;
	return retval;
}

int main() {
	mypair <int> x (10, 8);
	mypair <float> y (2.2, 5.5);

	cout << x.getmax() << endl;
	cout << y.getmax() << endl;
	return 0;
}