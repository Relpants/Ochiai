
#ifndef COMIC_H
#define COMIC_H

#include <unordered_map>
#include <string>
#include <iostream>


class Comic {
	public:
		Comic() = default;
		~Comic() = default;
		void set(int id_in, std::string name_in, int year_in, int issue_in);
		int Id();
		std::string Name();
		int Year();
		int Issue();

	private:
		int id;
		std::string name;
		int year;
		int issue;
};

#endif