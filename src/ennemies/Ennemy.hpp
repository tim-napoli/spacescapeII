#ifndef _Ennemy_hpp_
#define _Ennemy_hpp_

#include <list>

#include "lab/game/BehavioredEntity.hpp"
#include "lab/math/Vector.hpp"
#include "lab/math/Box.hpp"

#include "Explosion.hpp"
#include "Projectile.hpp"
#include "Player.hpp"

namespace ennemy {

class FollowBehavior;
class StopBehavior;
class ShootBehavior;
class MoveBehavior;
class AvoidBehavior;

class LinkMustShoot;

class Ennemy : public lab::game::BehavioredEntity {

	protected:
		float mAngle;
	
		int mLife;
		int mScore;
		
		bool mShoot;
		int mShootSpeed; // The minimum shoot speed of the object (to avoid firing each ticks, which is an ugly thing).
		int mShootProb; // The probability to shoot when shoot_count >= shoot_speed.
		int mShootCount;
		ShootParticle* mShootParticles;
		
		float mMaxAcceleration, mMaxSpeed;
		lab::math::Vector<float> mAcceleration;
		
		bool mToDelete;
		
		static std::list<Projectile*>* 			projectiles; // Projectiles.
		static Player**				   			player; 		// Player.
		static lab::graphic::ParticleSystem* 	particles;
	
	public:
		Ennemy (int mass,
				lab::math::Vector<float> 	position,
				lab::math::Vector<float> 	speed,
				lab::math::Box<float> 		box,
				float angle,
				int nbehaviors,
				int life, int score, int shoot_speed, int shoot_prob, ShootParticle* shoot_particles,
				float max_acceleration, float max_speed);
		
		~Ennemy ();
		
		virtual void update ();
		
		virtual void cycle () throw (lab::Exception);
	
		virtual void shoot ();
		
		virtual Explosion* getExplosion () const = 0;
		
		bool mustShoot () const {return mShoot;}
		
		bool toDelete () const {return mToDelete;}
		
		bool isDead () const {return mLife <= 0;}
		
		void addDamages (int d) {mLife -= d;}
		
		const lab::math::Vector<float>& getAcceleration () const {return mAcceleration;}
		
		int getScore () const {return mScore;}
		
		
		// Statiques
		static void setProjectiles (std::list<Projectile*>* p);
		
		static void setPlayer (Player** p);
		
		static void setParticleSystem (lab::graphic::ParticleSystem* sys) {particles = sys;}
		
		// Friends (all behaviors and links).
		friend class ennemy::FollowBehavior;
		friend class ennemy::StopBehavior;
		friend class ennemy::ShootBehavior;
		friend class ennemy::MoveBehavior;
		friend class ennemy::AvoidBehavior;
		
		friend class ennemy::LinkMustShoot;
};

}

#endif

