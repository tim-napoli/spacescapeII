#include "graphic/Text.hpp"

namespace lab {
namespace graphic {

Text::Text (const math::Vector<int>& position, const math::Vector<int>& hot_point, float angle, int zindex, 
	  		ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::string text, int flags) : 
		Drawable (position, math::Vector<int> (), hot_point, angle, zindex) {
	mFont = font;
	mColor = color;
	mText = al_ustr_new (text.c_str ());
	mFlags = flags;
}

Text::Text (const math::Vector<int>& position, const math::Vector<int>& hot_point, float angle, int zindex, 
	  		ALLEGRO_FONT* font, ALLEGRO_COLOR color, ALLEGRO_USTR* text, int flags) : 
		Drawable (position, math::Vector<int> (), hot_point, angle, zindex) {
	mFont = font;
	mColor = color;
	mText = al_ustr_dup (text);
	mFlags = flags;
}


Text::~Text () {
	al_ustr_free (mText);
}

void Text::draw () const {
	al_draw_ustr (mFont, mColor, 0.0f, 0.0f, mFlags, mText);
}

}}

