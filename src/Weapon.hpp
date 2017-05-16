#ifndef _Weapon_hpp_
#define _Weapon_hpp_

#include <list>

#include "lab/graphic/ParticleEmitter.hpp"

#include "Projectile.hpp"

class Weapon {
	public:
		const static int WEAPON_MAIN	= 0;
		const static int WEAPON_AUX		= 1;
		const static int WEAPON_SPEC	= 2;
	
	protected:
		int mType;
		int mSpeed, mCounter;
		
		lab::graphic::ParticleEmitter* mEmitter;
		
	public:
		Weapon (int type,
				int speed,
				const lab::graphic::ParticleEmitter* emitter);
		
		~Weapon ();
		
		int getType () const {return mType;}
		int getSpeed () const {return mSpeed;}
		int getCounter () const {return mCounter;}
		
		void setType (int type) {mType = type;}
		void setSpeed (int speed) {mSpeed = speed;}
		void setCounter (int counter) {mCounter = counter;}
		
		virtual Projectile* getProjectile () = 0;
		
		void shoot (std::list<Projectile*>& projectiles);
};

#endif

