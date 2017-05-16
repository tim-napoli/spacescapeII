#ifndef _Particles_hpp_
#define _Particles_hpp_

#include <allegro5/allegro.h>

#include "lab/graphic/ParticleEmitter.hpp"
#include "lab/math/Vector.hpp"

/************************************************* ShootParticle ******************************************************/
class ShootParticle : public lab::graphic::ParticleEmitter {
	private:
		lab::math::Vector<float>* mPosition;
		lab::math::Vector<float>  mOffset;
		
		// Paramètres des particules produites.
		int	mSize, mLifeMin, mLifeMax;
		float mMinSx, mMinSy, mMaxSx, mMaxSy;
		float mMinAx, mMinAy, mMaxAx, mMaxAy;
		ALLEGRO_COLOR mColor;
		ALLEGRO_BITMAP* mBitmap;
	
	public:
		ShootParticle (lab::graphic::ParticleSystem* particle_system, int spawn_num,
					   lab::math::Vector<float>* position, lab::math::Vector<float> offset,
					   int size, int life_min, int life_max, 
					   float min_speed_x, float min_speed_y, float max_speed_x, float max_speed_y,
					   float min_acc_x, float min_acc_y, float max_acc_x, float max_acc_y,
					   ALLEGRO_COLOR color, ALLEGRO_BITMAP* bmp);
		
		~ShootParticle ();
		
		void generateParticle (lab::graphic::particle* part);
		
		void setOffset (const lab::math::Vector<float> v) {mOffset = v;} 
};

#endif

