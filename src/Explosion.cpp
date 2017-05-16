#include "Explosion.hpp"

using namespace lab::math;
using namespace lab::graphic;

ParticleSystem* Explosion::particle_system = NULL;
ALLEGRO_BITMAP* Explosion::sprite = NULL;

Explosion::Explosion (const lab::math::Vector<float>& center, const lab::math::Vector<float>& speed, 
					  float speed_ini, float accel_ini, int size, int spawn_num, int life, ALLEGRO_COLOR color) :
			ParticleEmitter (Explosion::particle_system, 1, spawn_num) {
	mCenter = center;
	mSpeed = speed;
	mLife = life;
	mSize = size;
	mSpeedIni = speed_ini;
	mAccelIni = accel_ini;
	mColor = color;
}

Explosion::~Explosion () {

}

#define my_rand(min,max)	(rand()/(double)RAND_MAX)*(max-min)+min

void Explosion::generateParticle (particle* part) {

	Vector<float> speed (my_rand (0.0f, mSpeedIni), 0.0f);
	speed.rotate (Vector<float> (), (rand () % 628) * 0.01);
	
	Vector<float> accel (my_rand (0.0f, mAccelIni), 0.0f);
	accel.rotate (Vector<float> (), (rand () % 628) * 0.01);

	Vector<int> center = (Vector<int>) mCenter;
	
	init_particle_addr (part,
						center.x, center.y,
						speed.x, speed.y,
						accel.x, accel.y,
						mSize + rand () % mSize, mSize + rand () % mSize,
						5 + rand () % 10,
						mColor,
						Explosion::sprite);
}

void Explosion::update () {
	ParticleEmitter::update ();
	mLife--;
	
	mCenter += mSpeed;
	mSpeed *= 0.9f;
}

