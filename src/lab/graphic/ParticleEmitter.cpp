#include "lab/graphic/ParticleEmitter.hpp"
#include <iostream>

namespace lab {
namespace graphic {

ParticleEmitter::ParticleEmitter (ParticleSystem* target, int spawn_rate, int spawn_num) {
	mTarget = target;
	
	mSpawnRate = spawn_rate;
	mSpawnNum = spawn_num;
	mSpawnCount = 0;
}

ParticleEmitter::~ParticleEmitter () {

}

void ParticleEmitter::update () {
	// Look if a new particle must be created.
	if (mSpawnRate > 0) {
		mSpawnCount = (mSpawnCount + 1) % mSpawnRate;
		if (mSpawnCount == 0) {
		    particle p;
			for (int i = 0; i < mSpawnNum; i++) {
				generateParticle (&p);
				mTarget->addParticle(p);
			}
		}
	}
}

}}

