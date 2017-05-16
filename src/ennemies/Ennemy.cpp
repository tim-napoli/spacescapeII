#include "ennemies/Ennemy.hpp"

namespace ennemy {

std::list<Projectile*>* Ennemy::projectiles 	= NULL;
Player**				Ennemy::player 			= NULL;
lab::graphic::ParticleSystem* Ennemy::particles = NULL;

Ennemy::Ennemy (int mass,
		lab::math::Vector<float> 	position,
		lab::math::Vector<float> 	speed,
		lab::math::Box<float> 		box,
		float angle,
		int nbehaviors,
		int life, int score, int shoot_speed, int shoot_prob, ShootParticle* shoot_particles,
		float max_acceleration, float max_speed) :
			BehavioredEntity (mass, position, speed, box, nbehaviors) {
	mLife = life;
	mScore = score;
	
	mShootSpeed = shoot_speed;
	mShootProb = shoot_prob;
	mShootCount = 0;
	mShootParticles = shoot_particles;
	
	mMaxAcceleration = max_acceleration;
	mMaxSpeed = max_speed;
	mAngle = angle;
	
	mToDelete = false;
}

Ennemy::~Ennemy () {
	
}

void Ennemy::update () {
	BehavioredEntity::update ();
	
	if (mAcceleration.x != 0.0f || mAcceleration.y != 0.0f) {
		if ((mSpeed + mAcceleration).length () < mMaxSpeed) {
			mSpeed += mAcceleration;
		}
		else {
			mSpeed *= 0.9f;
			if (mSpeed.length () < 1) {
				mSpeed = lab::math::Vector<float> ();
			}
		}
	}
	else {
		mSpeed *= 0.9f;
		if (mSpeed.length () < 1) {
			mSpeed = lab::math::Vector<float> ();
		}
	}
	
	// Syncronization de l'angle du drawable.
	if (mDrawable != NULL) {
		mDrawable->setAngle (mAngle);
		//mDrawable->setAngle (mSpeed.angle () - ALLEGRO_PI * 0.5);
	}
	
	if (mShootParticles != NULL) {
		mShootParticles->update ();
	}
}

void Ennemy::cycle () throw (lab::Exception) {
	BehavioredEntity::cycle ();
	
	mShootCount++;
	if (mShootParticles != NULL && mShootCount == mShootSpeed) {
		mShootParticles->setSpawnRate (0);
	}
}

void Ennemy::shoot () {
	mShootCount = 0;
	mShoot = false;
	if (mShootParticles != NULL) {
		mShootParticles->setSpawnRate (1);
	}
}

void Ennemy::setProjectiles (std::list<Projectile*>* p) {
	Ennemy::projectiles = p;
}

void Ennemy::setPlayer (Player** p) {
	Ennemy::player = p;
}

}
