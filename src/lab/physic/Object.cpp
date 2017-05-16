#include "physic/Object.hpp"

#include <iostream>

namespace lab {
namespace physic {

Object::Object (int mass, 
				const math::Vector<float>& position, 
				const math::Vector<float>& speed,
				const math::Box<float>& box) {
	mMass = mass;
	mPosition = position;
	mSpeed = speed;
	mBox = box;
	mTakedInFace = math::Vector<float> ();
}

Object::~Object () {
	
}

void Object::apply (const math::Vector<float>& f) {
	mTakedInFace += f;
}

void Object::update () {
	mSpeed += mTakedInFace;
	mPosition += mSpeed;
	mTakedInFace = math::Vector<float> ();
}

bool Object::isCollide (const Object* object) {
	return getBox ().intersects (object->getBox ());
}

bool Object::handleCollision (Object* object) {
	if (isCollide (object)) {
		math::Vector<float> this_force = (mSpeed * (mMass - object->getMass ()) + object->getSpeed () * (2 * object->getMass ())) / (mMass + object->getMass ());
		//?\\ N'est il pas judicieux de traiter indépendemment les deux objets ? Si object devient le sujet de la collision dans le même tour ?
		math::Vector<float> object_force = (object->getSpeed () * (object->getMass () - mMass) + mSpeed * (2 * mMass)) / (mMass + object->getMass ());

		object->apply (object_force - object->getSpeed ());
		apply (this_force - mSpeed);
		
		return true;
	}
	
	return false;
}

}}

