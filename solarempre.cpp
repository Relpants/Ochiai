#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "ship.h"

int main(int argc, char *argv[]){

	Ship phantom;
	phantom.ship_name("phantom");
	phantom.ship_classification("destroyer");
	phantom.ship_armaments("phase missles");

	phantom.ship_id();
	return 0;
}