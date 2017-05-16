#include "Background.hpp"

using namespace lab;
using namespace lab::graphic;
using namespace lab::math;

Background::Background (ALLEGRO_BITMAP* background) :
		Drawable (Vector<int> (), Vector<int> (), Vector<int> (), 0.0f, 0) {
	mBackground = background;
	mOffset = al_get_bitmap_height (mBackground);
	
	for (int i = 0; i < 50; i++) {
		mStars [i].x = rand () % 960;
		mStars [i].y = rand () % 540;
		
		mStars [i].speed = 0.1 + (rand () % 30) * 0.1;
		
		mStars [i].base_color = 175;
		mStars [i].color = 175;
		mStars [i].color_amp = 50.0f;
		
		mStars [i].radius = (5 + rand () % 10) * 0.1f;
		
		mStars [i].counter = (rand () % 314) * 0.01f;
		mStars [i].counter_speed = (rand () % 100) / 1000.0f;
	}
}

Background::~Background () {

}

void Background::update () {
	for (int i = 0; i < 50; i++) {
		star* s = &(mStars [i]);
		s->y += s->speed;
		if (s->y > 540) {
			s->y = 0;
		}
		
		s->counter += s->counter_speed;
		if (s->counter > 2 * ALLEGRO_PI) {
			s->counter -= 2 * ALLEGRO_PI;
		}
		s->color = s->
		base_color + (int) (s->color_amp * cos (s->counter));
	}
	
	mOffset--;
	if (mOffset < 0) {
		mOffset = al_get_bitmap_height (mBackground);
	}
}

void Background::draw () const {
	// Arrive à la fin.
	if (mOffset > al_get_bitmap_height (mBackground) - 540) {
		al_draw_bitmap_region (mBackground, 0.0f, mOffset, 960.0f, al_get_bitmap_height (mBackground), 0.0f, 0.0f, 0);
		al_draw_bitmap_region (mBackground, 0.0f, 0.0f, 960.0f, 540 - (al_get_bitmap_height (mBackground) - mOffset), 0.0f, (al_get_bitmap_height (mBackground) - mOffset), 0);
	}
	else {
		al_draw_bitmap_region (mBackground, 0.0f, mOffset, 960.0f, mOffset + 540.0f, 0.0f, 0.0f, 0);
	}
	
	for (int i = 0; i < 50; i++) {
		ALLEGRO_COLOR color = al_map_rgb (mStars [i].color, mStars [i].color, mStars [i].color);

		al_draw_filled_circle (mStars [i].x, mStars [i].y, mStars [i].radius * 0.8, color);
	}
}

