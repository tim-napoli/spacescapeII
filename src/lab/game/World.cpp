#include "lab/game/World.hpp"

namespace lab {
namespace game {

World::World () {

}

World::~World () {

}

std::list<BehavioredEntity*>* World::getGroup ( const std::string& group ) const throw (lab::Exception) {
	auto got = mEntityGroups.find ( group );
	if (got == mEntityGroups.end ()) {
		throw lab::Exception (0, "World::getGroup error : cannot find group \"" + group + "\".");
	}
	
	return got->second;
}

void World::cycle () {

}


}}

