#include "graphic/Drawable.hpp"

namespace lab {
namespace graphic {

Drawable::Drawable (const math::Vector<int>& position, 
				    const math::Vector<int>& dimensions,
				    const math::Vector<int>& hot_point,
					float angle,
				    int zindex) {
	mPosition = position;
	mDimensions = dimensions;
	mHotPoint = hot_point;
	mAngle = angle;
	mZindex = zindex;
}

Drawable::~Drawable () {

}

void Drawable::getReady () {
	ALLEGRO_TRANSFORM T;
	
	al_identity_transform (&T);
	// Rotation
	al_translate_transform (&T, -(mDimensions.x >> 1), -(mDimensions.y >> 1));
	al_rotate_transform (&T, mAngle);
	// Translation
	math::Vector<int> true_pos = mPosition - mHotPoint + (mDimensions / 2);
	al_translate_transform (&T, true_pos.x, true_pos.y);
	// Composition avec la transformation précédente.
	al_compose_transform (&T, al_get_current_transform ());

	// Utilisation de la transformation.
	al_use_transform (&T);
}

}}
