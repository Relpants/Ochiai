#include "comic.h"


void Comic::set(int id_in, const std::string name_in, int issue_in, int year_in){
	id = id_in;
	name = name_in;
	issue = issue_in;
	year = year_in;
}

int Comic::Id() {
	return id;
}

int Comic::Year() {
	return year;
}

int Comic::Issue() {
	return issue;
}

std::string Comic::Name() {
	return name;
}