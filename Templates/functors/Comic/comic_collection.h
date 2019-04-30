
#ifndef COMIC_COLLECTION_H
#define COMIC_COLLECTION_H


#include <unordered_map>
#include <string>
#include <iostream>
#include "comic.h"
class ComicCollection {
	public:
		ComicCollection() = default;
		~ComicCollection() = default;
		bool AddtoCollection(int id, Comic comic);


		template <typename Functor>
		bool AddtoList(int id, Comic comic, Functor&& f){
			std::cout << "In functor" << std::endl;
			auto str = Comic_list.find(id);
			if(str == Comic_list.end()) {
				Comic_list[id] = std::move(comic);
			}

			f(Comic_list);
			std::cout << "after call" << std::endl;
			return true;
			std::cout << "What about this " << std::endl;
		}

	private:
		std::unordered_map<int, Comic> Comic_list;
};

#endif 