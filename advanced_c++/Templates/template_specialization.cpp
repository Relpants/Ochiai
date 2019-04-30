//template specialization

#include <iostream>
using namespace std;

//class template that handles any type other than char
template <class T>
class myContainer {
	T element;
  public:
  	myContainer(T arg) { 
  		element = arg;
  	}
  	T increase () {
  		cout << "Calling template" << endl;
  		return ++element;
  	}
};

//class template specialization
//in this case the specialization is char
template <> 
class myContainer <char> {  // the specialization is char
	char element;
  public:
  	myContainer(char arg) { 
  		element = arg;
  	}
  	char uppercase (){
  		cout << "Calling template specialization" << endl;
  		if ((element > 'a') && (element < 'z'))
  			element += 'A' - 'a';
  		return element;
  	}
};

int main() {
	myContainer<int> myint (2);     // calls the 'first' template class
	myContainer<char> mychar('x');    // calls the template specialization since it shares type

	cout << myint.increase() << endl;
	cout << mychar.uppercase() << endl;

	return 0;
}