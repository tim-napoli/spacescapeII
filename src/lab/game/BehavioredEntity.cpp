#include "lab/game/World.hpp"
#include "lab/game/Behavior.hpp"
#include "lab/game/BehavioredEntity.hpp"
#include "lab/physic/Object.hpp"

namespace lab {
namespace game {

World* BehavioredEntity::world = NULL;

BehavioredEntity::BehavioredEntity (int mass, 
								    const math::Vector<float>& position, 
								    const math::Vector<float>& speed,
								    const math::Box<float>& box,
								    int nbehaviors) : Entity (mass, position, speed, box) {
	mNBehaviors = nbehaviors;
	mCurrentBehavior = NULL;
	mBehaviors = new Behavior* [nbehaviors];
	for (int i = 0; i < nbehaviors; i++) {
		mBehaviors [i] = NULL;
	}
}

BehavioredEntity::~BehavioredEntity () {
	if (mCurrentBehavior != NULL) {
		Entity::renderer->removeDrawable (mCurrentBehavior->getDrawable ());
	}

	for (int i = 0; i < mNBehaviors; i++) {
		if (mBehaviors [i] != NULL) {
			delete mBehaviors [i];
		}
	}
	
	delete mBehaviors;
}

void BehavioredEntity::setDrawable (int behavior) {
	if (mCurrentBehavior != NULL) {
		Entity::renderer->removeDrawable (mCurrentBehavior->getDrawable ());
	}
	
	Entity::renderer->addDrawable (mBehaviors [behavior]->getDrawable ());
	mDrawable = mBehaviors [behavior]->getDrawable ();
	syncronizeDrawable ();
}

void BehavioredEntity::update () {
	physic::Object::update ();
	
	// Regarde si on peut utiliser un autre comportement.
	std::vector<BehaviorLink*> links = mCurrentBehavior->getLinks ();
	for (unsigned int i = 0; i < links.size (); i++) {
		if (links [i]->check ()) {
			mCurrentBehavior->onUnset ();
			// Modification du drawable.
			setDrawable (links [i]->getBehavior ());
			// Mise à jour du comportement.
			setCurrentBehavior (links [i]->getBehavior ());
			mCurrentBehavior->onSet ();
			break;
		}
	}
}

void BehavioredEntity::cycle () throw (Exception) {
	if (mCurrentBehavior == NULL) {
		throw Exception (0, "BehavioredEntity::cycle warning : No current behavior is set.");
	}
	
	// Utilisation du comportement.
	mCurrentBehavior->cycle ();
}


}}

