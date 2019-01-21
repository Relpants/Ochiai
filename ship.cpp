#include "ship.h"
#include <iostream>


void Ship::ship_id(){
	std::cout << "Ship name: " << name << std::endl;
	std::cout << "The ship classification is: " << classification << std::endl;
	std::cout << "The ship's armaments are: " << armaments << std::endl;
}