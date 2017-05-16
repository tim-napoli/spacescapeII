#include "lab/game/BehavioredEntity.hpp"
#include "lab/game/Behavior.hpp"

namespace lab {
namespace game {

Behavior::Behavior (graphic::Drawable* drawable, int nlinks) {
	mDrawable = drawable;
	mLinks.resize (nlinks);
}

Behavior::~Behavior () {
	delete mDrawable;
	for (unsigned int i = 0; i < mLinks.size (); i++) {
		delete mLinks [i];
	}
	mLinks.clear ();
}

}}

