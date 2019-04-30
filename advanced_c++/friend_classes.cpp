// friend class example 

#include <iostream>

using namespace std;

class CSquare; //empty declaration so we can declare Csquare on line 15

class CRectangle {
	int width, height;
  public:
  	int area(){
  		return (width*height);
  	}
  	void convert (CSquare a);  // function that is using friend property
};

class CSquare {
	private:
		int side;
	public:
		void set_side(int a){
			side = a;
		}
		int area(){
			return (side*4);
		}
		friend class CRectangle;	// declaring CRectangle a friend of CSquare
								// this means Crectangle can access Csquares private and public members
};

void CRectangle::convert(CSquare a){
	width = a.side;
	height = a.side;
}

// One thing to note is that CSquare is not a friend of CRectangle
// CSquare would have to be explicity declared a friend in CRectangle

// Another property of friendships is that they are not transitive:
// The friend of a friend is not considered to be a friend 
// IT MUST BE DECLARED EXPLICITLY

int main () {
	CSquare sqr;
	CRectangle rec;

	sqr.set_side(4);
	cout << sqr.area() << endl;

	rec.convert(sqr);
	cout << rec.area() << endl;

	return 0;

}