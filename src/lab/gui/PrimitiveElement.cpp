#include "lab/gui/PrimitiveElement.hpp"

#include <allegro5/allegro_primitives.h>

using namespace lab;
using namespace lab::math;
using namespace lab::gui;
using namespace lab::graphic;

namespace lab {
namespace gui {

PrimitiveElement::PrimitiveElement (const lab::math::Vector<int> position, const lab::math::Vector<int> dimensions, int zindex,
				  ALLEGRO_COLOR color_top, ALLEGRO_COLOR color_bottom,
				  ALLEGRO_COLOR border_color, int border_type, int border_width) :
		Element (position, dimensions, zindex),
		mColorTop (color_top), mColorBottom (color_bottom),
		mBorderColor (border_color), mBorderType (border_type), mBorderWidth (border_width) {
				  
}

PrimitiveElement::~PrimitiveElement () {

}

void PrimitiveElement::draw () const {

	{ // <
	unsigned char tr, tg, tb;
	unsigned char br, bg, bb;
	float sr, sg, sb;
	al_unmap_rgb (mColorTop, &tr, &tg, &tb);
	al_unmap_rgb (mColorBottom, &br, &bg, &bb);
	sr = (br - tr) / (float) mDimensions.y;
	sg = (bg - tg) / (float) mDimensions.y;
	sb = (bb - tb) / (float) mDimensions.y;
	
	for (int y = 0; y < mDimensions.y; y++) {
		al_draw_filled_rectangle (0, y, mDimensions.x, y + 1, al_map_rgb (tr + sr * y, tg + sg * y, tb + sb * y));
	}
	} // >
	
	{ // <
	unsigned char r1, g1, b1;
	unsigned char r2, g2, b2;
	
	al_unmap_rgb (mBorderColor, &r1, &g1, &b1);
	r2 = 128 + (128 - r1);
	g2 = 128 + (128 - g1);
	b2 = 128 + (128 - b1);
	
	switch (mBorderType) {
		case BORDER_SOLID:
			al_draw_filled_rectangle (0, 0, 
									  mDimensions.x, mBorderWidth, 
									  mBorderColor);
			al_draw_filled_rectangle (0, mDimensions.y - mBorderWidth, 
									  mDimensions.x, mDimensions.y, 
									  mBorderColor);
			al_draw_filled_rectangle (0, 0, 
									  mBorderWidth, mDimensions.y, 
									  mBorderColor);
			al_draw_filled_rectangle (mDimensions.x - mBorderWidth, 0, 
									  mDimensions.x, mDimensions.y, 
									  mBorderColor);
			break;
		
		case BORDER_INSET:
			// Top
			al_draw_filled_rectangle (0, 0, 
									  mDimensions.x - mBorderWidth, mBorderWidth, 
									  mBorderColor);
			al_draw_filled_triangle (mDimensions.x - mBorderWidth, 0,
									 mDimensions.x, 0,
									 mDimensions.x - mBorderWidth, mBorderWidth,
									 mBorderColor);
			
			// Bottom
			al_draw_filled_triangle (mBorderWidth, mDimensions.y - mBorderWidth,
									 mBorderWidth, mDimensions.y,
									 0, mDimensions.y,
									 al_map_rgb (r2, g2, b2));
			al_draw_filled_rectangle (mBorderWidth, mDimensions.y - mBorderWidth, 
									  mDimensions.x, mDimensions.y, 
									  al_map_rgb (r2, g2, b2));
			
			// Left			  
			al_draw_filled_rectangle (0, 0, 
									  mBorderWidth, mDimensions.y - mBorderWidth, 
									  mBorderColor);
			al_draw_filled_triangle (0, mDimensions.y - mBorderWidth,
									 mBorderWidth, mDimensions.y - mBorderWidth,
									 0, mDimensions.y,
									 mBorderColor);
			
			// Right
			al_draw_filled_triangle (mDimensions.x - mBorderWidth, mBorderWidth,
									 mDimensions.x, 0,
									 mDimensions.x, mBorderWidth,
									 al_map_rgb (r2, g2, b2));			  
			al_draw_filled_rectangle (mDimensions.x - mBorderWidth, mBorderWidth, 
									  mDimensions.x, mDimensions.y, 
									  al_map_rgb (r2, g2, b2));
			break;
		
		case BORDER_OUTSET:
			// Top
			al_draw_filled_rectangle (0, 0, 
									  mDimensions.x - mBorderWidth, mBorderWidth, 
									  al_map_rgb (r2, g2, b2));
			al_draw_filled_triangle (mDimensions.x - mBorderWidth, 0,
									 mDimensions.x, 0,
									 mDimensions.x - mBorderWidth, mBorderWidth,
									 al_map_rgb (r2, g2, b2));
			
			// Bottom
			al_draw_filled_triangle (mBorderWidth, mDimensions.y - mBorderWidth,
									 mBorderWidth, mDimensions.y,
									 0, mDimensions.y,
									 mBorderColor);
			al_draw_filled_rectangle (mBorderWidth, mDimensions.y - mBorderWidth, 
									  mDimensions.x, mDimensions.y, 
									  mBorderColor);
			
			// Left			  
			al_draw_filled_rectangle (0, 0, 
									  mBorderWidth, mDimensions.y - mBorderWidth, 
									  al_map_rgb (r2, g2, b2));
			al_draw_filled_triangle (0, mDimensions.y - mBorderWidth,
									 mBorderWidth, mDimensions.y - mBorderWidth,
									 0, mDimensions.y,
									 al_map_rgb (r2, g2, b2));
			
			// Right
			al_draw_filled_triangle (mDimensions.x - mBorderWidth, mBorderWidth,
									 mDimensions.x, 0,
									 mDimensions.x, mBorderWidth,
									 mBorderColor);			  
			al_draw_filled_rectangle (mDimensions.x - mBorderWidth, mBorderWidth, 
									  mDimensions.x, mDimensions.y, 
									  mBorderColor);
			break;
	}
	} // >
}

}}

