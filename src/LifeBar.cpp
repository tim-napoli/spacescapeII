#include "LifeBar.hpp"

using namespace lab;
using namespace lab::graphic;
using namespace lab::math;

LifeBar::LifeBar (const Vector<int>& position, Player** player, Resources* resources)
		: Drawable (position, Vector<int> (200, 10), Vector<int> (), 0.0f, 102) {
	mPlayer = player;
	mBackground = resources->getBitmap ("lifebar_back");
	mForground = resources->getBitmap ("lifebar_for");
}

LifeBar::~LifeBar () {

}

void LifeBar::draw () const {
	if (*mPlayer) {
		float prop = (*mPlayer)->getLife () / 100.0f;
		
		al_draw_scaled_bitmap (mBackground, 
							   0, 0, al_get_bitmap_width (mBackground) * prop, al_get_bitmap_height (mBackground),
							   0, 0, mDimensions.x * prop, mDimensions.y,
							   0);
	}
	al_draw_scaled_bitmap (mForground, 
						   0, 0, al_get_bitmap_width (mForground), al_get_bitmap_height (mForground),
						   0, 0, mDimensions.x, mDimensions.y,
						   0);
}

