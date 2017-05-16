#include "lab/gui/Element.hpp"

using namespace lab;
using namespace lab::math;
using namespace lab::gui;
using namespace lab::graphic;

Element::Element (const Vector<int>& position, const Vector<int>& dimensions, int zindex) :
		Drawable (position, dimensions, Vector<int> (), 0.0f, zindex) {

}

Element::~Element () {

}



