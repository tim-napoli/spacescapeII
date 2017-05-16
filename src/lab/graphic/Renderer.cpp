#include "graphic/Renderer.hpp"
#include <allegro5/allegro_primitives.h>

namespace lab {
namespace graphic {

Renderer::Renderer (const math::Vector<int>& virtual_dimensions, const io::Video* video, bool scale) {
	//mObjects = boost::map<int, std::list<Drawable*>> ();
	mDimensions = virtual_dimensions;
	mVideo = video;
	mScale = scale;
	mTrembleCount = 0;
	
	updateInfos ();
}

Renderer::~Renderer () {
	for (auto it = mObjects.begin (); it != mObjects.end (); ++it) {
		it->second.clear ();
	}
	mObjects.clear ();
}

bool Renderer::hasDrawable (Drawable* addr) const {
	// Vérification de présence de l'index.
	auto got_sec = mObjects.find (addr->getZindex ());
	if (got_sec == mObjects.end ()) {
		return false;
	}
	
	// Regarde dans la liste correspondant au zindex.
	for (auto it = got_sec->second.begin (); it != got_sec->second.end (); ++it) {
		if (*it == addr) {
			return true;
		}
	}

	return false;
}

void Renderer::addDrawable (Drawable* addr) throw (lab::Exception) {
	if (hasDrawable (addr)) {
		throw lab::Exception (0, "Renderer::addDrawable error : Already in !");
	}
	
	auto got_sec = mObjects.find (addr->getZindex ());
	if (got_sec == mObjects.end ()) {
		mObjects.insert (std::map<int, std::list<Drawable*>>::value_type (addr->getZindex (), std::list<Drawable*> ()) );
		got_sec = mObjects.find (addr->getZindex ());
	}
	
	got_sec->second.push_front (addr);
}

void Renderer::removeDrawable (Drawable* addr) throw (lab::Exception) {
	if (!hasDrawable (addr)) {
		throw lab::Exception (0, "Renderer::removeDrawable error : Not exists !");
	}

	auto got_sec = mObjects.find (addr->getZindex ());
	for (std::list<Drawable*>::iterator it = got_sec->second.begin (); it != got_sec->second.end (); ++it) {
		if (addr ==  *it) {
			got_sec->second.erase (it);
			break;
		}
	}
}

void Renderer::render () {
	al_use_transform (&mTransform);

	// Drawing the objects
	ALLEGRO_TRANSFORM pushed;
	al_copy_transform (&pushed, &mTransform);
	for (auto it_sec = mObjects.begin (); it_sec != mObjects.end (); ++it_sec) {
		for (auto it = it_sec->second.begin (); it != it_sec->second.end (); ++it) {
			(*it)->getReady ();
			(*it)->draw ();
			al_use_transform (&pushed);
		}
	}
	
	// Barres noires, pour masquer l'imperfection.
	al_identity_transform (&pushed);
	al_use_transform (&pushed);
	if (mBarres) {
		al_draw_filled_rectangle (mBarA.getLeft (), mBarA.getTop (), mBarA.getRight (), mBarA.getBottom (), al_map_rgb (0, 0, 0));
		al_draw_filled_rectangle (mBarB.getLeft (), mBarB.getTop (), mBarB.getRight (), mBarB.getBottom (), al_map_rgb (0, 0, 0));
	}
	
	// Load default transformation for the display.
	al_use_transform (&mTransform);
}

void Renderer::updateInfos () {
	// Prepare the transformation to scale to the right dimensions.
	al_identity_transform (&mTransform);
	if (mScale) {
		float scale_x = mVideo->getWidth () / (float) mDimensions.x;
		float scale_y = mVideo->getHeight () / (float) mDimensions.y;
		al_scale_transform (&mTransform, scale_x, scale_y);
		
		mBarres = false;
	}
	else {
		float vratio = mDimensions.x / (float) mDimensions.y;
		float sratio = mVideo->getWidth () / (float) mVideo->getHeight ();
		float scale_x, scale_y;
		float tx, ty;

		// Barres horizontales
		if (vratio > sratio) {
			scale_x = mVideo->getWidth () / (float) mDimensions.x;
			scale_y = (mVideo->getWidth () * (1.0 / vratio)) / (float) mDimensions.y;
			tx = 0.0f;
			ty = (mVideo->getHeight () - (mVideo->getWidth () * (1.0 / vratio))) / 2;
			
			mBarA = math::Box<int> (0, 0, mVideo->getWidth (), ty);
			mBarB = math::Box<int> (0, mVideo->getHeight () - ty, mVideo->getWidth (), mVideo->getHeight ());
			mBarres = true;
		}
		// Barres verticales
		else if (vratio < sratio) {
			scale_y = mVideo->getHeight () / (float) mDimensions.y;
			scale_x = (mVideo->getHeight () * (vratio)) / (float) mDimensions.x;
			tx = (mVideo->getWidth () - (mVideo->getHeight () * (vratio))) / 2;
			ty = 0.0f;
			
			mBarA = math::Box<int> (0, 0, tx, mVideo->getHeight ());
			mBarB = math::Box<int> (mVideo->getWidth () - tx, 0, mVideo->getWidth (), mVideo->getHeight ());	
			mBarres = true;
		}
		else {
			scale_x = mVideo->getWidth () / (float) mDimensions.x;
			scale_y = mVideo->getHeight () / (float) mDimensions.y;
			tx = 0.0f;
			ty = 0.0f;
			
			mBarres = false;
		}
		//al_set_clipping_rectangle (tx, ty, mVideo->getWidth () - tx, mVideo->getHeight () - ty);
		al_scale_transform (&mTransform, scale_x, scale_y);
		al_translate_transform (&mTransform, tx, ty);
	}
}

}}

