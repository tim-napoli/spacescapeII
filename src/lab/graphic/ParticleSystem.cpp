#include "lab/graphic/ParticleSystem.hpp"

namespace lab {
namespace graphic {

ParticleSystem::ParticleSystem (math::Vector<int> dimensions, int zindex, unsigned int max_particles) :
		Drawable (math::Vector<int> (), dimensions, math::Vector<int> (), 0.0f, zindex) {
	mMaxSize = max_particles;
	
	mParticles = std::list<particle>();
	
	al_set_new_bitmap_flags (ALLEGRO_VIDEO_BITMAP | ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	mBuffer = al_create_bitmap (dimensions.x, dimensions.y);
}

ParticleSystem::~ParticleSystem () {
	al_destroy_bitmap (mBuffer);
	
	mParticles.clear ();
}

void ParticleSystem::addParticle(const particle& p) {
    if (mParticles.size () < mMaxSize) {
        mParticles.push_back(p);
    }            
}

void ParticleSystem::update () {
    for (auto it = mParticles.begin (); it != mParticles.end (); it++) {
        if ((*it).life == 0) {
            it = mParticles.erase (it);
            it--;
        }
        else {
            (*it).life--;
            (*it).sx += (*it).ax;
            (*it).sy += (*it).ay;
            (*it).x += (*it).sx;
            (*it).y += (*it).sy;
        }
    }
}

void ParticleSystem::draw () const {
	// Store current states.
	ALLEGRO_BITMAP* pushed_buffer;
	ALLEGRO_TRANSFORM pushed_transform;
	al_copy_transform (&pushed_transform, al_get_current_transform ());
	pushed_buffer = al_get_target_bitmap ();
	int op, src, dest;
	al_get_blender (&op, &src, &dest);
	
	// Changing target buffer.
	al_set_target_bitmap (mBuffer);
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_use_transform (&transform);
	
	// Setting a blender.
	al_set_blender (ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
	
	// Draw the particles
	al_clear_to_color (al_map_rgba (0, 0, 0, 0));
	for (auto it = mParticles.begin(); it != mParticles.end(); it++) {
	    al_draw_tinted_scaled_bitmap (	(*it).bitmap, 
										(*it).color,
										0, 0, al_get_bitmap_width ((*it).bitmap), 
									  	      al_get_bitmap_height ((*it).bitmap),
										(*it).x, (*it).y, (*it).w, (*it).h,
										0
								  	  );
	}
	
	// Restore saved states.
	al_set_target_bitmap (pushed_buffer);
	al_use_transform (&pushed_transform);
	al_set_blender (op, src, dest);
	al_draw_bitmap (mBuffer, 0, 0, 0); // TODO - Use al_draw_scaled_bitmap (faster than transformation ?).
	
	// Done !
}

void ParticleSystem::clearParticles () {
	mParticles.clear ();
}

}}


