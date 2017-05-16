#ifndef _Explosion_hpp_
#define _Explosion_hpp_

#include <allegro5/allegro.h>

#include "lab/graphic/ParticleEmitter.hpp"

class Explosion : public lab::graphic::ParticleEmitter {
	private:
		lab::math::Vector<float> mCenter, mSpeed;
		float mSpeedIni, mAccelIni;
		
		int mLife;
		int mSize;
		
		ALLEGRO_COLOR mColor;
	
		static lab::graphic::ParticleSystem* particle_system;
		static ALLEGRO_BITMAP* sprite;
	
	public:
		Explosion (const lab::math::Vector<float>& center, const lab::math::Vector<float>& speed, 
				   float speed_ini, float accel_ini, int size, int spawn_num, int life, ALLEGRO_COLOR color);
		
		~Explosion ();
	
		void generateParticle (lab::graphic::particle* part);
		
		void update ();
		
		bool isDead () {return mLife <= 0;}
	
		static void setParticleSystem (lab::graphic::ParticleSystem* particle_system) {Explosion::particle_system = particle_system;}
		
		static void setSprite (ALLEGRO_BITMAP* bmp) {Explosion::sprite = bmp;}
};

#endif

