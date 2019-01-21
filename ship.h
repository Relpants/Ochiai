
#include <string>

#ifndef SHIP_H_
#define SHIP_H_

class Ship {
	private:
		std::string classification;
		std::string armaments;
		std::string name;
	public:
		void ship_name(std::string n) { name = n; }
		void ship_classification(std::string c) { classification = c;}
		void ship_armaments(std::string a) { armaments = a;}
		void ship_id();
};
#endif // SHIP_H_