#include "graphic/Animation.hpp"

namespace lab {
namespace graphic {

Animation::Animation (const math::Vector<int>& position, float angle, int zindex, int tick_ratio, int mode, int num_frames) : 
		Drawable (position, math::Vector<int> (), math::Vector<int> (), angle, zindex) {
	mDrawables.resize (num_frames);
	mTickRatio = tick_ratio;
	mSpeed = 1;
	mCounter = 0;
	mMode = mode;
	mCurrentFrame = 0;
}

Animation::~Animation () {
	for (unsigned int i = 0; i < mDrawables.size (); i++) {
		delete mDrawables [i];
	}
	mDrawables.clear ();
}

void Animation::update () {
	mCounter = (mCounter + 1) % mTickRatio;
	
	if (mCounter == 0) {
		switch (mMode) {
			case MODE_REVERSE:
				if (mCurrentFrame == mDrawables.size () - 1 || mCurrentFrame == 0) {
					mSpeed = -mSpeed;
				}
				break;
		
			case MODE_SINGLE:
				if (mCurrentFrame == mDrawables.size () - 1) {
					mSpeed = 0;
				}
				break;
		}
	}
	
	mCurrentFrame += mSpeed;
}

void Animation::draw () const {
	ALLEGRO_TRANSFORM saved;
	al_copy_transform (&saved, al_get_current_transform ());
	
	mDrawables [mCurrentFrame]->getReady ();
	mDrawables [mCurrentFrame]->draw ();
	
	al_use_transform (&saved);
}

}}


