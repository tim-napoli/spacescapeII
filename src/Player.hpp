#ifndef _Player_hpp_
#define _Player_hpp_

#include "lab/Resources.hpp"
#include "lab/activity/Activity.hpp"
#include "lab/graphic/ParticleEmitter.hpp"
#include "lab/graphic/ParticleSystem.hpp"
#include "lab/graphic/Sprite.hpp"
#include "lab/game/BehavioredEntity.hpp"
#include "lab/game/Behavior.hpp"
#include "lab/game/BehaviorLink.hpp"

#include "Projectile.hpp"
#include "Explosion.hpp"
#include "Particles.hpp"

#include <list>

class PropulsionParticles : public lab::graphic::ParticleEmitter {
	private:
		lab::math::Vector<float>* mPlayerPosition, *mPlayerSpeed;
		ALLEGRO_BITMAP* mParticleBitmap;

	public:
		PropulsionParticles (lab::graphic::ParticleSystem* particle_sys, 
							 lab::math::Vector<float>* player_position, 
							 lab::Resources* resources);
		
		~PropulsionParticles ();
		
		void generateParticle (lab::graphic::particle* part);
};

/* Behavior wait */
class PlayerBehaviorWaitToMove : public lab::game::BehaviorLink {
	private:
		lab::math::Vector<float>* mAcceleration;
		
	public:
		PlayerBehaviorWaitToMove (lab::math::Vector<float>* acceleration);
		
		~PlayerBehaviorWaitToMove ();
		
		bool check ();
};

class PlayerBehaviorWait : public lab::game::Behavior {
	private:
		lab::math::Vector<float>* mSpeed;
		lab::math::Vector<float>* mAcceleration;

	public:
		PlayerBehaviorWait (lab::graphic::Sprite* sprite, lab::math::Vector<float>* speed, lab::math::Vector<float>* acceleration);
		
		~PlayerBehaviorWait ();
		
		void onSet ();
		
		void cycle ();
		
		void onUnset ();
};

/* Behavior move */
class PlayerBehaviorMoveToWait : public lab::game::BehaviorLink {
	private:
		lab::math::Vector<float>* mAcceleration;
		
	public:
		PlayerBehaviorMoveToWait (lab::math::Vector<float>* acceleration);
		
		~PlayerBehaviorMoveToWait ();
		
		bool check ();
};

class PlayerBehaviorMove : public lab::game::Behavior {
	private:
		lab::math::Vector<float>* mSpeed;
		lab::math::Vector<float>* mAcceleration;
		
		PropulsionParticles* mParticles;
		
		int mGo;

	public:
		PlayerBehaviorMove (lab::graphic::Sprite* sprite, lab::math::Vector<float>* speed, lab::math::Vector<float>* acceleration, PropulsionParticles* particles);
		
		~PlayerBehaviorMove ();
		
		void onSet ();
		
		void cycle ();
		
		void onUnset ();
};

/***************************************************** Player *********************************************************/
class Player : public lab::game::BehavioredEntity {
	public:
		static const int WAIT = 0;
		static const int MOVE = 1;
	
	private:
		bool mWantToMove;	// Le joueur bouge.
		
		lab::math::Vector<float> mAcceleration;
		PropulsionParticles* mParticles;
		ShootParticle* mShootParticles;
		
		bool mShoot;		// Le joueur tire.
		int  mShootCounter, mLastShoot;
		int  mShootCount;   // Number of projectiles emitteds (only main).
		int  mShootTouched; // Number of projectiles which touch (only main).
		bool mLaserLeft;
		int  mPower;
		ALLEGRO_BITMAP* mGreenProjectile, *mGreenLaser, *mRedLaser, *mRedProjectile;
		
		int mLife;
		int mShield;
		
		//Weapon *mMainWeapon, *mAuxWeapon, *mSpecWeapon;
	
	public:
		Player (const lab::math::Vector<float>& position, 
				lab::Resources* resources, 
				lab::graphic::ParticleSystem* particle_sys);
		
		~Player ();
		
		void cycle () throw (lab::Exception);
		
		void update ();
		
		bool shooting () const {return mShoot;}
		
		void setShoot (bool b) {mShoot = b; mShootCounter = 0;}
		
		void shoot (std::list<Projectile*>* projectiles);
		
		void setWantToMove (bool b) {mWantToMove = b;}
		
		
		bool isDead () const {return mLife <= 0;}
		
		void addDamages (int d);
		
		void addLife (int l) {mLife += l; if (mLife > 100) {mLife = 100;}}
		
		void addShield (int l) {mShield += l; if (mShield > 100) mShield = 100;}
		
		int getLife () const {return mLife;}
		
		int getShield () const {return mShield;}
		
		int getPower () const {return mPower;}
		
		void setPower (int power) {mPower = power;}
		
		void incShootTouched() {mShootTouched++;}
		
		
		void addAcceleration (const lab::math::Vector<float>& v) {mAcceleration += v;}
		
		const lab::math::Vector<float>& getAcceleration () const {return mAcceleration;}
		
		void setPropulsion (bool b) {if (b) {mParticles->setSpawnRate (10);} else {mParticles->setSpawnRate (0);}}
		
		
		const lab::math::Vector<float>* getPositionAddress () const {return &mPosition;}
		
		Explosion* getExplosion () const;
};

/* Tasks */
class PlayerMoveTask : public lab::activity::Task {
	private:
		Player** mPlayer;
		lab::math::Vector<float> mSpeed;
	
	public:
		PlayerMoveTask (Player** player, lab::math::Vector<float> speed);
		
		~PlayerMoveTask ();
	
		void execute (const lab::event::Event& event) const;
};

class PlayerShootTask : public lab::activity::Task {
	private:
		Player** mPlayer;
	
	public:
		PlayerShootTask (Player** player);
		
		~PlayerShootTask ();
	
		void execute (const lab::event::Event& event) const;
};

#endif

