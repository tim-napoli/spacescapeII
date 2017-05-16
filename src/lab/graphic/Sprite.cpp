#include "graphic/Sprite.hpp"

namespace lab {
namespace graphic {

int Sprite::FLIP_X = 0x1;
int Sprite::FLIP_Y = 0x2;

Sprite::Sprite (const math::Vector<int>& position, const math::Vector<int>& dimensions, const math::Vector<int>& hot_point, float angle, int zindex,
				int flags, ALLEGRO_BITMAP* bitmap) :
		Drawable (position, dimensions, hot_point, angle, zindex) {
	mFlags = flags;
	mBitmap = bitmap;
}

Sprite::~Sprite () {

}

void Sprite::draw () const {
	int flags = 0;

	if ((mFlags & FLIP_X) == 1) {
		flags |= ALLEGRO_FLIP_HORIZONTAL;
	}
	if ((mFlags & FLIP_Y) == 1) {
		flags |= ALLEGRO_FLIP_VERTICAL;
	}

	al_draw_scaled_bitmap (	mBitmap, 
							0, 0, al_get_bitmap_width (mBitmap), al_get_bitmap_height (mBitmap),
							0, 0, mDimensions.x, mDimensions.y,
							flags);
}

}}

