#ifndef _lab_gui_PrimitiveElement_hpp_
#define _lab_gui_PrimitiveElement_hpp_

#include "lab/gui/Element.hpp"

namespace lab {
namespace gui {

class PrimitiveElement : public Element {
	public:
		static const int BORDER_NONE 	= -1;
		static const int BORDER_SOLID 	= 0;
		//static const int BORDER_GROOVE 	= 1;
		static const int BORDER_INSET 	= 2;
		static const int BORDER_OUTSET 	= 3;
	
	protected:
		ALLEGRO_COLOR mColorTop, mColorBottom; // Gradient.
		
		ALLEGRO_COLOR mBorderColor;
		int mBorderType, mBorderWidth;
	
	public:
		PrimitiveElement (const lab::math::Vector<int> position, const lab::math::Vector<int> dimensions, int zindex,
						  ALLEGRO_COLOR color_top, ALLEGRO_COLOR color_bottom,
						  ALLEGRO_COLOR border_color, int border_type, int border_width);
		
		virtual ~PrimitiveElement ();
		
		virtual void draw () const;
		
		virtual bool onKeyChar (int unichar, int keycode) = 0;
		
		virtual bool onMouseClick (int button) = 0;
		
		virtual bool onMouseOver (int x, int y) = 0;
};

}}

#endif

