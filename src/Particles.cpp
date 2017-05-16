#include "Particles.hpp"

using namespace lab::graphic;
using namespace lab::math;

#define my_rand(min,max)	(rand()/(double)RAND_MAX)*(max-min)+min

/************************************************* ShootParticle ******************************************************/
ShootParticle::ShootParticle (lab::graphic::ParticleSystem* particle_system, int spawn_num,
			   				  lab::math::Vector<float>* position, lab::math::Vector<float> offset,
			   				  int size, int life_min, int life_max, 
			   				  float min_speed_x, float min_speed_y, float max_speed_x, float max_speed_y,
					   		  float min_acc_x, float min_acc_y, float max_acc_x, float max_acc_y,
			   				  ALLEGRO_COLOR color, ALLEGRO_BITMAP* bmp) :
		ParticleEmitter (particle_system, 0, spawn_num) {
	mPosition = position;
	mOffset = offset;
	
	mSize = size;
	mLifeMin = life_min;
	mLifeMax = life_max;
	
	mMinSx = min_speed_x;
	mMinSy = min_speed_y;
	mMaxSx = max_speed_x;
	mMaxSy = max_speed_y;
	
	mMinAx = min_acc_x;
	mMinAy = min_acc_y;
	mMaxAx = max_acc_x;
	mMaxAy = max_acc_y;
	
	mColor = color;
	mBitmap = bmp;
}

ShootParticle::~ShootParticle () {

}

void ShootParticle::generateParticle (particle* part) {
	init_particle_addr (part,
						mPosition->x + mOffset.x, mPosition->y + mOffset.y,
						my_rand (mMinSx, mMaxSx), my_rand (mMinSy, mMaxSy),
						my_rand (mMinAx, mMaxAx), my_rand (mMinAy, mMaxAy),
						mSize, mSize,
						my_rand (mLifeMin, mLifeMax),
						mColor,
						mBitmap
					   );
}

