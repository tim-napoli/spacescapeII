#ifndef _lab_gui_Element_hpp_
#define _lab_gui_Element_hpp_

#include "lab/graphic/Drawable.hpp"

namespace lab {
namespace gui {

class Element : public lab::graphic::Drawable {
	public:
		Element (const lab::math::Vector<int>& position, const lab::math::Vector<int>& dimensions, int zindex);
		
		virtual ~Element ();
	
		virtual void draw () const = 0;
		
		
};

}}

#endif

