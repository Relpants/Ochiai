#include <utility>
#include "comic_collection.h"

bool ComicCollection::AddtoCollection(int32_t id, Comic comic) {
    Comic_list[id] = std::move(comic);
	return true;
}
