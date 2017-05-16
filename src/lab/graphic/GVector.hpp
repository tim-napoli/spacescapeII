#ifndef _lab_graphic_GVector_hpp_
#define _lab_graphic_GVector_hpp_

#include <allegro5/allegro.h>

#include "lab/math/Vector.hpp"
#include "lab/graphic/Drawable.hpp"

namespace lab {
namespace graphic {

template <typename T>
class GVector : public Drawable {
	private:
		math::Vector<T> mVector;
		float mWidth;
		float mScale;
		ALLEGRO_COLOR mColor;
		
	public:
		GVector (const math::Vector<int>& position, const math::Vector<T>& vector, ALLEGRO_COLOR mColor, float width, float scale, int zindex);
		
		~GVector ();
		
		void update (const math::Vector<int>& position, const math::Vector<T>& vector);
		
		void draw () const;
};

template <typename T>
GVector<T>::GVector (const math::Vector<int>& position, const math::Vector<T>& vector, ALLEGRO_COLOR color, float width, float scale, int zindex)
		: Drawable (position, math::Vector<int> (), math::Vector<int> (), 0.0f, zindex), 
			mVector (vector) {
	mColor = color;
	mWidth = width;
	mScale = scale;
}

template <typename T>
GVector<T>::~GVector () {

}

template <typename T>
void GVector<T>::update (const math::Vector<int>& position, const math::Vector<T>& vector) {
	mPosition = position;
	mVector = vector;
}

template <typename T>
void GVector<T>::draw () const {
	al_draw_line (0, 0, mVector.x * mScale, mVector.y * mScale, mColor, mWidth);
}

}}

#endif

