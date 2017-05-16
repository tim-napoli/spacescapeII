#ifndef _ennemy_Behaviors_hpp_
#define _ennemy_Behaviors_hpp_

#include "lab/game/Behavior.hpp"
#include "lab/graphic/Drawable.hpp"
#include "lab/math/Vector.hpp"
#include "lab/math/Polygon.hpp"

#include "ennemies/Ennemy.hpp"

namespace ennemy {

/**************************************************** Behaviors *******************************************************/
class Behavior : public lab::game::Behavior {
	protected:
		Ennemy* mEnnemy;
	
	public:
		Behavior (Ennemy* ennemy, int nlinks, lab::graphic::Drawable* drawable);
		
		~Behavior ();
		
		virtual void onSet () {};
		
		virtual void cycle () = 0;
		
		virtual void onUnset () {};
};

class ShootBehavior : public ennemy::Behavior {
	private:
		int mShootTime, mShootCount;
		int mActionTime;
	
	public:
		ShootBehavior (Ennemy* ennemy, int shoot_time, int action_time, lab::graphic::Drawable* drawable, int after);
		
		~ShootBehavior ();
		
		void cycle ();
		
		void onUnset ();
};


class FollowBehavior : public ennemy::Behavior {
	private:
		const lab::math::Vector<float>* mTargetPosition;
		lab::math::Vector<float> mDifference;
	
	public:
		FollowBehavior (Ennemy* ennemy,
						const lab::math::Vector<float>* target_position, 
						const lab::math::Vector<float>& difference, 
						lab::graphic::Drawable* drawable,
						int stop_beha);
		FollowBehavior (Ennemy* ennemy,
						const lab::math::Vector<float>* target_position, 
						const lab::math::Vector<float>& difference, 
						lab::graphic::Drawable* drawable,
						int shoot_behavior, int stop_beha);
		/*FollowBehavior (Ennemy* ennemy,
						const Vector<float>* target_position, 
						const Vector<float>& difference, 
						lab::graphic::Drawable* drawable,
						int shoot_behavior, int avoid_behavior);*/
		
		~FollowBehavior ();
		
		void cycle ();
		
		void setDifference (const lab::math::Vector<float>& diff) {mDifference = diff;}
		
};

class StopBehavior : public ennemy::Behavior {
	public:
		StopBehavior (Ennemy* ennemy,
					  lab::graphic::Drawable* drawable,
					  int after);
		
		~StopBehavior ();
		
		void onSet ();
		
		void cycle ();
};

class MoveBehavior : public ennemy::Behavior {
	private:
		lab::math::Vector<float> mSpeed;

	public:
		MoveBehavior (Ennemy* ennemy, lab::graphic::Drawable* drawable, 
					  const lab::math::Vector<float>& speed, int shoot_beha);
		//DirectMoveBehavior (Ennemy* ennemy, int shoot_beha, int avoid_beha);
		
		~MoveBehavior ();
		
		void cycle ();
};

class AvoidBehavior : public ennemy::Behavior {
    private:
        static std::list<Projectile*>* mProjectiles;     // Projectiles to avoid.
        float  mCareArea;                                // Area around the ennemy where a projectile should not be.
    
    public:
        AvoidBehavior (Ennemy* ennemy, lab::graphic::Drawable* drawable,
                       float care_area);
        
        ~AvoidBehavior ();
        
        void cycle ();
};

/*
class AvoidBehavior : public ennemy::Behavior {
	private:
		
		lab::math::Polygon<float> mViewField;		 // Will only see objects in this polygon (from the face of the ship).
		int mConsciousnessSize;						 // Number of things the ennemy can try to avoid at the same time.
		std::vector<Projectile*> mConsciousness;	 // Consciousness
		int mErrorMargin;							 // The percentage of chance to calculate a bad trajectory (will 
													 // have a random reaction).
		static std::list<Projectile*>* projectiles;  // Player projectiles.
	
	public:
		AvoidBehavior (Ennemy* ennemy, lab::graphic::Drawable* drawable, 
					   const lab::math::Polygon<float>& view_field, int consciousness_size, 
					   int error_margin, int after_beha);
		
		~AvoidBehavior ();
		
		void cycle ();
		
		
		
		static void setProjectiles (std::list<Projectile*>* p) {AvoidBehavior::projectiles = p;}
};
*/

}

#endif

