#include "game/Entity.hpp"

namespace lab {
namespace game {

graphic::Renderer* Entity::renderer = NULL;

Entity::Entity (int mass, 
			    const math::Vector<float>& position, 
			    const math::Vector<float>& speed,
			    const math::Box<float>& box) :
		physic::Object (mass, position, speed, box) 
		{
	mDrawable = NULL;
}

Entity::~Entity () {

}

void Entity::syncronizeDrawable () {
	if (mDrawable != NULL) {
		mDrawable->setPosition ((math::Vector<int>) mPosition);
	}
}

}}

