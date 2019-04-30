#include <iostream>

using namespace std;

template <class T>
T GetMax(T a, T b){
	T result;
	result = (a>b)? a : b;
	return result;
}

int main() {

	int i=5,j=6,k;
	long l=10,z=11,x;
	float a=1.1,b=2.2,c;

	k = GetMax<int>(i,j);
	x = GetMax<long>(l,z);
	c = GetMax<float>(a,b);

	cout << k << endl;
	cout << x << endl;
	cout << c << endl;

	return 0;
}