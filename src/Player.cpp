#include "Player.hpp"
#include "lab/math/Box.hpp"

using namespace lab;
using namespace lab::game;
using namespace lab::graphic;
using namespace lab::math;

#define my_rand(min,max)	(rand()/(double)RAND_MAX)*(max-min)+min

/* Propulsion Particles */
PropulsionParticles::PropulsionParticles (lab::graphic::ParticleSystem* particle_sys, 
										  lab::math::Vector<float>* player_position, 
										  lab::Resources* resources) :
		ParticleEmitter (particle_sys, 0, 10) {
	mParticleBitmap = resources->getBitmap ("star");
	mPlayerPosition = player_position;
}

PropulsionParticles::~PropulsionParticles () {

}

void PropulsionParticles::generateParticle (particle* part) {
	init_particle_addr (part,
						mPlayerPosition->x + 12, mPlayerPosition->y + 32,
						my_rand (-1.0, 1.0), 0.1,
						my_rand (-0.005, 0.005), my_rand (0.005, 0.015),
						24, 24,
						my_rand (6, 16),
						al_map_rgba (my_rand (0, 100), my_rand (0, 100), my_rand (200, 255), 10),
						mParticleBitmap
					   );
}


/* BehaviorLink wait -> move */
PlayerBehaviorWaitToMove::PlayerBehaviorWaitToMove (Vector<float>* acceleration) : BehaviorLink (1) {
	mAcceleration = acceleration;
}

PlayerBehaviorWaitToMove::~PlayerBehaviorWaitToMove () {

}

bool PlayerBehaviorWaitToMove::check () {
	return (mAcceleration->length () > 0);
}

/* Behavior wait */
PlayerBehaviorWait::PlayerBehaviorWait (Sprite* sprite, lab::math::Vector<float>* speed, Vector<float>* acceleration) : Behavior (sprite, 1) {
	setLink (0, new PlayerBehaviorWaitToMove (acceleration));
	mSpeed = speed;
	mAcceleration = acceleration;
}

PlayerBehaviorWait::~PlayerBehaviorWait () {

}

void PlayerBehaviorWait::onSet () {

}

void PlayerBehaviorWait::cycle () {
	(*mSpeed) = (*mSpeed) * 0.9f;
	if (mSpeed->length () < 1) {mSpeed->x = 0; mSpeed->y = 0;}
}

void PlayerBehaviorWait::onUnset () {

}


/* BehaviorLink move -> wait */
PlayerBehaviorMoveToWait::PlayerBehaviorMoveToWait (Vector<float>* acceleration) : BehaviorLink (0) {
	mAcceleration = acceleration;
}

PlayerBehaviorMoveToWait::~PlayerBehaviorMoveToWait () {

}

bool PlayerBehaviorMoveToWait::check () {
	return (mAcceleration->length () == 0);
}

/* Behavior move */
PlayerBehaviorMove::PlayerBehaviorMove (Sprite* sprite, lab::math::Vector<float>* speed, Vector<float>* acceleration, PropulsionParticles* particles) : Behavior (sprite, 1) {
	setLink (0, new PlayerBehaviorMoveToWait (acceleration));
	mSpeed = speed;
	mAcceleration = acceleration;
	
	mGo = 0;
	
	mParticles = particles;
}

PlayerBehaviorMove::~PlayerBehaviorMove () {

}

void PlayerBehaviorMove::onSet () {
	mParticles->setSpawnRate (1);
}

void PlayerBehaviorMove::cycle () {
	mGo = (mGo + 1) % 5;

	if (mAcceleration->x == 0) {
		if (mSpeed->x < -1) {
			mSpeed->x++;
		}
		else if (mSpeed->x > 0) {
			mSpeed->x--;
		}
	}
	
	if (mAcceleration->y == 0) {
		if (mSpeed->y < 0) {
			mSpeed->y++;
		}
		else if (mSpeed->y > 0) {
			mSpeed->y--;
		}
	}
		
	if (mGo == 1) {
		if (mSpeed->x < 24 && mSpeed->x > -24) {
			mSpeed->x += mAcceleration->x;
		}
	
		if (mSpeed->y < 24 && mSpeed->y > -24) {
			mSpeed->y += mAcceleration->y;
		}
	}
}

void PlayerBehaviorMove::onUnset () {
	mParticles->setSpawnRate (0);
}

/* Player */
Player::Player (const Vector<float>& position, lab::Resources* resources, lab::graphic::ParticleSystem* particle_sys) :
		BehavioredEntity (50, position, Vector<float> (), Box<float> (4, 4, 44, 44), 2) {
	mShoot = false;
	mWantToMove = false;
	
	mAcceleration = Vector<float> ();
	mParticles = new PropulsionParticles (particle_sys, &mPosition, resources);
	
	mShootParticles = new ShootParticle (particle_sys, 5,
										 &mPosition, Vector<float> (18, -8),
										 12, 3, 15,
										 -0.5f, -0.2f, 0.5f, -0.2f, 
										 -0.01f, -0.005f, 0.005f, -0.015f,
										 al_map_rgba (50, 200, 32, 10),
										 resources->getBitmap ("star")
										);
	
	
	setBehavior (0, new PlayerBehaviorWait (new Sprite (Vector<int> (), Vector<int> (48, 48), Vector<int> (), 0.0f, 100, 0, resources->getBitmap ("player")),
											&mSpeed, &mAcceleration)
				);
	
	setBehavior (1, new PlayerBehaviorMove (new Sprite (Vector<int> (), Vector<int> (48, 48), Vector<int> (), 0.0f, 100, 0, resources->getBitmap ("player")),
											&mSpeed, &mAcceleration, mParticles)
				);
	
	setDrawable (0);
	setCurrentBehavior (0);
	
	mPower = 1;
	mShootCounter = 0;
	mLastShoot = 0;
	mShootCount = 0;
	mGreenProjectile = resources->getBitmap ("pproj1");
	mRedProjectile = resources->getBitmap ("pproj2");
	mGreenLaser = resources->getBitmap ("laserg");
	mRedLaser = resources->getBitmap ("laserr");
		
	mLife = 100;
	mShield = 0;
	
	mLaserLeft = true;
}
		
Player::~Player () {
	delete mParticles;
	delete mShootParticles;
}

void Player::addDamages(int d) {
    if (mShield > 0) {
        mShield -= d;
        if (mShield < 0) {
            mLife += mShield;
            mShield = 0;
        }
    }
    else {
        mLife -= d;
    }
}

void Player::cycle () throw (Exception) {
	BehavioredEntity::cycle ();
	
	if (mPosition.x + mSpeed.x < 0) {
		mPosition.x = 0;
		mSpeed.x = 0;
	}	
	else if (mPosition.x + mSpeed.x + 48 > 960) {
		mPosition.x = 960 - 48;
		mSpeed.x = 0;
	}
	
	if (mPosition.y + mSpeed.y < 0) {
		mPosition.y = 0;
		mSpeed.y = 0;
	}	
	else if (mPosition.y + mSpeed.y + 48 > 540) {
		mPosition.y = 540 - 48;
		mSpeed.y = 0;
	}
}

void Player::update () {
	BehavioredEntity::update ();
	mParticles->update ();	
	mShootParticles->update ();
	
	if (mLastShoot > 0) {
		mLastShoot--;
		if (mLastShoot == 0) {
			mShootParticles->setSpawnRate (0);
		}
	}
}

void Player::shoot (std::list<Projectile*>* projectiles) {
	if (mShootCounter == 0) {
		switch (mPower) {
			case 1:
			case 2:
				projectiles->push_front (new Projectile (5, 
				                                         mPosition + Vector<float> (18, -12 + (rand () % 4) * 6), 
				                                         Vector<float> (0, -12),
				                                         Box<float> (0, 0, 8, 8), 
														 new Sprite (Vector<float> (), Vector<float> (12, 12), Vector<float> (), 0, 100, 0, mGreenProjectile ), 
														 10, 
														 10, 
														 true,
														 0.3f,
														 12.0f, 
														 15, 
														 al_map_rgba (32, 100, 16, 10)
														) 
										);
				break;
		    
		    case 3:
		    case 4:
		        // Missile rouge
		        projectiles->push_front (new Projectile (5, 
		                                                 mPosition + Vector<float> (22, -8 + (rand () % 4) * 6),
		                                                 Vector<float> (0, -12),
		                                                 Box<float> (0, 0, 8, 8), 
														 new Sprite (Vector<float> (), Vector<float> (8, 8), Vector<float> (), 0, 100, 0, mRedProjectile ), 
														 20, 
														 10, 
														 true,
														 0.3f, 12.0f, 15, al_map_rgba (100, 16, 16, 10)
														) 
										);
		        break;
		}
		
		mShootParticles->setSpawnRate (1);
		mLastShoot = 2;
		mShootCount++;
	}
	
	
	// Petits missiles
	if (mPower > 1) {
		// A gauche
		if (mShootCounter == 9) {
			if (mLaserLeft) {
				projectiles->push_front (new Projectile (1, mPosition + Vector<float> (5, 12), Vector<float> (0, -8), Box<float> (0, 0, 4, 16), 
														   new Sprite (Vector<float> (), Vector<float> (4, 16), Vector<float> (), 0, 100, 0, mGreenLaser), 
														   5, 1, false, 0.2f, 8.0f, 10, al_map_rgba (32, 100, 16, 10)
														) 
										);
				mLaserLeft = false;
			}
			else {
				projectiles->push_front (new Projectile (1, mPosition + Vector<float> (38, 12), Vector<float> (0, -8), Box<float> (0, 0, 4, 16), 
													     new Sprite (Vector<float> (), Vector<float> (4, 16), Vector<float> (), 0, 100, 0, mGreenLaser), 
													     5, 1, false, 0.2f, 8.0f, 10, al_map_rgba (32, 100, 16, 10)
													   ) 
										);
				mLaserLeft = true;
			}
		}
	}
	
	// Petit missile rouge
	if (mPower > 3) {
	    if (mShootCounter == 5) {
			if (mLaserLeft) {
				projectiles->push_front (new Projectile (1, mPosition + Vector<float> (5, 4), Vector<float> (-4, -4), Box<float> (0, 0, 4, 16), 
														   new Sprite (Vector<float> (), Vector<float> (4, 16), Vector<float> (), -0.785f, 100, 0, mRedLaser), 
														   10, 1, false, 0.2f, 8.0f, 10, al_map_rgba (100, 16, 16, 10)
														) 
										);
			}
			else {
				projectiles->push_front (new Projectile (1, mPosition + Vector<float> (38, 4), Vector<float> (4, -4), Box<float> (0, 0, 4, 16), 
														   new Sprite (Vector<float> (), Vector<float> (4, 16), Vector<float> (), +0.785f, 100, 0, mRedLaser), 
														   10, 1, false, 0.2f, 8.0f, 10, al_map_rgba (100, 16, 16, 10)
														) 
										);
			}
		}
	}
	
	mShootCounter = (mShootCounter + 1) % 10;
}

Explosion* Player::getExplosion () const {
	return new Explosion (mPosition + (getDimensions () * 0.5) - Vector<float> (10, 10), mSpeed, 0.6f, 0.1f, 20, 50, 50, al_map_rgba (50, 50, 225, 10));
}

/* Move Task */
PlayerMoveTask::PlayerMoveTask (Player** player, lab::math::Vector<float> speed) {
	mPlayer = player;
	mSpeed = speed;
}
		
PlayerMoveTask::~PlayerMoveTask () {

}

void PlayerMoveTask::execute (const lab::event::Event& event) const {
	(void) event;
	
	if (*mPlayer != NULL) {
		if (	(mSpeed.x > 0 && (*mPlayer)->getAcceleration ().x <= 0)
			||	(mSpeed.x < 0 && (*mPlayer)->getAcceleration ().x >= 0)
			||	(mSpeed.y > 0 && (*mPlayer)->getAcceleration ().y <= 0)
			||	(mSpeed.y < 0 && (*mPlayer)->getAcceleration ().y >= 0)) {
	
			(*mPlayer)->addAcceleration (mSpeed);
		}
	}
}

/* Shoot Task */
PlayerShootTask::PlayerShootTask (Player** player) {
	mPlayer = player;
}
		
PlayerShootTask::~PlayerShootTask () {

}

void PlayerShootTask::execute (const lab::event::Event& event) const {
	(void) event;
	if (*mPlayer != NULL) {
		(*mPlayer)->setShoot (!(*mPlayer)->shooting ());
	}
}

