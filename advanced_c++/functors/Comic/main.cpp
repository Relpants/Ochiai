
#include <iostream>
#include "comic_collection.h"
#include "comic.h"
#include "string.h"
int main() {

	ComicCollection cc;

	Comic c1;
	c1.set(1, "IronMan", 314, 2012);

	Comic c2;
	c2.set(2, "Hulk", 226, 1988);

	cc.AddtoCollection(1, c1);

	int list_count=0;



	std::cout << "Before Functor " << list_count << std::endl;


	cc.AddtoList(2, c2, [&list_count] (std::unordered_map<int, Comic> c1) {
		list_count = c1.size();
		std::cout << "list size: " << list_count << std::endl;
		return true; 
	});

	std::cout << "After Functor" << std::endl;






	std::cin.get();
	
	return 0;

}