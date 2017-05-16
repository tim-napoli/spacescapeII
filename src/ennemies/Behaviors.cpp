#include "ennemies/Behaviors.hpp"
#include <cmath>

using namespace lab;
using namespace lab::math;


namespace ennemy {

/***************************************************** Behavior *******************************************************/
Behavior::Behavior (Ennemy* ennemy, int nlinks, lab::graphic::Drawable* drawable) : 
		lab::game::Behavior (drawable, nlinks) {
	mEnnemy = ennemy;
}

Behavior::~Behavior () {

}

/************************************************* Shoot Behaviors ****************************************************/
class LinkMustShoot : public lab::game::BehaviorLink {
	private:
		Ennemy* mEnnemy;
			
	public:
		LinkMustShoot (Ennemy* ennemy, int beha) : lab::game::BehaviorLink (beha) {
			mEnnemy = ennemy;
		}
		
		~LinkMustShoot () { }
		
		bool check ();
};

bool LinkMustShoot::check () {
	if (mEnnemy->mShootCount >= mEnnemy->mShootSpeed) {
		if (rand () % 100 < mEnnemy->mShootProb) {
			return true;
		}
	}
	
	return false;
}

class LinkShoot : public lab::game::BehaviorLink {
	private:
		bool mHaveShoot;
	
	public:
		LinkShoot (int beha) : lab::game::BehaviorLink (beha) {
			mHaveShoot = false;
		}
		
		~LinkShoot () { }
		
		void setHaveShoot (bool b) {mHaveShoot = b;}
		
		bool check () {return mHaveShoot;}
};

ShootBehavior::ShootBehavior (Ennemy* ennemy, int shoot_time, int action_time, 
							  lab::graphic::Drawable* drawable,
							  int after) : 
		Behavior (ennemy, 1, drawable) {
	setLink (0, new LinkShoot (after));
	
	mShootTime = shoot_time;
	mShootCount = 0;
	mActionTime = action_time;
}

ShootBehavior::~ShootBehavior () {

}

void ShootBehavior::cycle () {
	mShootCount++;

	if (mShootTime == mShootCount) {
		mEnnemy->mShoot = true;
	}

	if (mActionTime == mShootCount) {
		mShootCount = 0;
		((LinkShoot*) getLink (0))->setHaveShoot (true);
	}
}

void ShootBehavior::onUnset () {
	((LinkShoot*) getLink (0))->setHaveShoot (false);
}

/************************************************* Follow Behaviors ***************************************************/
class LinkRedirection : public lab::game::BehaviorLink {
	private:
		Ennemy* mEnnemy;
	
	public:
		LinkRedirection (Ennemy* ennemy, int beha) : lab::game::BehaviorLink (beha) {
			mEnnemy = ennemy;
		}
		
		~LinkRedirection () { }
		
		bool check ();
};

bool LinkRedirection::check () {
	float angle = mEnnemy->getSpeed ().angleBetween (Vector<float> (), mEnnemy->getAcceleration ());
	if (((angle > 1.4 && angle < 1.75) || (angle > 4.5 && angle < 4.85)) && mEnnemy->getSpeed ().length () > 0 && mEnnemy->getAcceleration ().length () > 0) {
		return true;
	}
	
	return false;
}

FollowBehavior::FollowBehavior (Ennemy* ennemy,
								const Vector<float>* target_position, 
								const Vector<float>& difference, 
								lab::graphic::Drawable* drawable,
								int stop_beha) :
		Behavior (ennemy, 1, drawable), mTargetPosition (target_position) {
	setLink (0, new LinkRedirection (ennemy, stop_beha));
	mDifference = difference;					
}

FollowBehavior::FollowBehavior (Ennemy* ennemy,
								const Vector<float>* target_position, 
								const Vector<float>& difference, 
								lab::graphic::Drawable* drawable,
								int shoot_beha, int stop_beha) :
		Behavior (ennemy, 2, drawable), mTargetPosition (target_position) {
	setLink (0, new LinkRedirection (ennemy, stop_beha));
	setLink (1, new LinkMustShoot (ennemy, shoot_beha));
	mDifference = difference;					
}

FollowBehavior::~FollowBehavior () {

}

void FollowBehavior::cycle () {
	if (*Ennemy::player != NULL) {
		// L'ennemi vise un point
		Vector<float> target_point = (*mTargetPosition) + mDifference;
	
		// Il va calculer son accélération en fonction de sa position.
		Vector<float> next_pos = mEnnemy->getPosition () + mEnnemy->getSpeed ();
		float dist_radius = mEnnemy->mMaxAcceleration;
	
		// Le nombre de tour nécessaire à s'arrêter : c'est n tel que 0.9^n * |vx| < 1 <=> 0.9^n < (1 / |vx|) (ou y).
		// n = |vx| > |vy| : ln (1 / |vx|) / ln (0.9) ? ln (1 / |vy|) / ln (0.9)
		// On ne prends pas ici en compte une éventuelle contre-poussée.
		int n = 0;
		if (std::abs (mEnnemy->mSpeed.x) != 0 && std::abs (mEnnemy->mSpeed.y) != 0) {
			n = ceil (( std::abs (mEnnemy->mSpeed.x) > std::abs (mEnnemy->mSpeed.y) )
						? std::log10 (1.0f / std::abs (mEnnemy->mSpeed.x)) / std::log10 (0.9f)
						: std::log10 (1.0f / std::abs (mEnnemy->mSpeed.y)) / std::log10 (0.9f));
		}
	
		// La distance nécessaire à s'arrêter c'est : somme (i : 1 -> n, ||v|| * 0.9^i)
		float coef = 0.9;
		float dist = 0.0f;
		float vlength = mEnnemy->mSpeed.length ();
		for (int i = 0; i < n; i++) {
			dist += vlength * coef;
			coef *= 0.9;
		}
	
		float real_dist = (target_point - mEnnemy->getPosition ()).length ();
		if (real_dist > dist) {
			// Calcul de la prochaine accélération.
			// On trace un cercle autour du point de prochaine position, ayant pour rayon la norme du vecteur de son 
			// vecteur d'accélération maximale.
			// On Trace ensuite le vecteur du point de prochaine position au point cible, puis on normalise ce vecteur et on le
			// multiplie par le rayon du cercle.
			Vector<float> diff = target_point - next_pos;
			if (dist_radius > diff.length ()) {
				dist_radius = diff.length ();
			}
			diff.normalize ();
			diff *= dist_radius;
	
			mEnnemy->mAcceleration = diff;
		}
		else {
			mEnnemy->mAcceleration = Vector<float> ();
		}
	}
	else {
		mEnnemy->mAcceleration = Vector<float> (0.0f, mEnnemy->mMaxAcceleration);
		if (mEnnemy->getPosition ().y > 540) {
			mEnnemy->mToDelete = true;
		}
	}
}

/************************************************** Stop Behavior *****************************************************/
class LinkStopped : public lab::game::BehaviorLink {
	private:
		Ennemy* mEnnemy;
	
	public:
		LinkStopped (Ennemy* ennemy, int beha) : lab::game::BehaviorLink (beha) {
			mEnnemy = ennemy;
		}
		
		~LinkStopped () { }
		
		bool check () {return (mEnnemy->getSpeed ().length () < 1);}
};

StopBehavior::StopBehavior (Ennemy* ennemy,
			  lab::graphic::Drawable* drawable,
			  int after) :
			Behavior (ennemy, 1, drawable) {
	setLink (0, new LinkStopped (ennemy, after));
}

StopBehavior::~StopBehavior () {
	
}

void StopBehavior::onSet () {
	mEnnemy->mAcceleration.x = 0;
	mEnnemy->mAcceleration.y = 0;
}

void StopBehavior::cycle () {
	/*mEnnemy->mSpeed *= 0.9;
	if (mEnnemy->mSpeed.length () < 1) {
		mEnnemy->mSpeed.x = 0.0f;
		mEnnemy->mSpeed.y = 0.0f;
	}*/
	// Devrait-on utiliser les réacteurs ?
}

/************************************************** Move Behavior *****************************************************/
MoveBehavior::MoveBehavior (Ennemy* ennemy, lab::graphic::Drawable* drawable, 
							const lab::math::Vector<float>& speed, int shoot_beha)
		: Behavior (ennemy, 1, drawable) {
	setLink (0, new LinkMustShoot (ennemy, shoot_beha));
	mSpeed = speed;
}
	
MoveBehavior::~MoveBehavior () {

}
		
void MoveBehavior::cycle () {
	if (mEnnemy->mSpeed.length () < mSpeed.length ()) {
		Vector<float> accel =  mSpeed;
		accel.normalize ();
		accel *= (mEnnemy->mMaxAcceleration);
		mEnnemy->mAcceleration = accel;
	}
	else {
		mEnnemy->mAcceleration = Vector<float> (0.0f, 0.0f);
	}
}

/************************************************** Avoid Behavior ****************************************************/
// Ce comportement doit permettre à un ennemi d'éviter les projectiles du joueur.
// 
class LinkFinishAvoid : public lab::game::BehaviorLink {
    private:
        Ennemy* mEnnemy;
        AvoidBehavior* mBehavior;
};

/*
// Comment déterminer qu'une demi-droite est en intersection avec une boite ?
//  

class LinkFinishAvoid : public lab::game::BehaviorLink {
	private:
		Ennemy* mEnnemy;
		AvoidBehavior* mBehavior;
		Polygon<float>* mViewField;
	
	public:
		LinkFinishAvoid (Ennemy* ennemy, int beha, std::list<Projectile*>* consciousness, Polygon<float>* view_field) : lab::game::BehaviorLink (beha) {
			mEnnemy = ennemy;
			mConsciousness = consciousness;
			mViewField = view_field;
		}
		
		~LinkFinishAvoid () { }
		
		bool check () {
			for (auto it = mProjectiles->begin ();
				 it != mProjectiles->end () && mBehavior->mConsciousness->size () < mBehavior->mMaxConsciousnessSize; 
				 it++) {
				// On regarde si ce projectile est dans le champ de vision de cet ennemi...
				if (mViewField->contains ((*it)->getPosition ()) {
					// Puis on regarde si ce projectile a une trajectoire dangereuse pour cet ennemi en fonction de
					// l'erreur possible d'évaluation (rotation de la trajectoire selon un certain angle aléatoire par 
					// exemple).
					    // 1) Récupérer le vecteur vitesse (vs) du projectile
					    // 2) Regarder si il existe t tel que (p + t * vs) soit dans la boite de collision de l'ennemi,
					    //    où p est la position du projectile.
					    //    On a le système (on postule t >= 0) :
					    //      | p(x) + t * vs(x) >= b1(x)
					    //      | p(x) + t * vs(x) <= b2(x)
					    //      | p(y) + t * vs(y) >= b1(y)
					    //      | p(y) + t * vs(y) <= b2(y)
					    //    Qui équivaut à :
					    //      | t >= (b1(x) - p(x)) / vs(x) (eq 1, si vs(x) != 0)
					    //      | t <= (b2(x) - p(x)) / vs(x) (eq 2, si vs(x) != 0)
					    //      | t >= (b1(y) - p(y)) / vs(y) (eq 3, si vs(y) != 0)
					    //      | t <= (b2(y) - p(y)) / vs(y) (eq 4, si vs(y) != 0)
                        //    Si les équations sont vérifiées pour au moins un t, alors ce t existe, sinon il n'existe 
                        //    pas.
                        //    Pour vérifier, on va déterminer si 
					    Vector<float> b1 = mEnnemy->getBox ().getPosition (),
					                  b2 = mEnnemy->getBox ().getPosition () + mEnnemy->getBox ().getDimensions ();
					    Vector<float> vs = (*it)->getSpeed ();
					    Vector<float> p = (*it)->getPosition ();
					    float txmin = (b1.x - p.x) / vs.x,
					          tymin = (b1.y - p.y) / vs.y,
					          txmax = (b2.x - p.x) / vs.x,
					          tymax = (b2.y - p.y) / vs.y;
					    float tmin = (txmin < tymin) ? txmin : tymin;
					    float tmax = (txmax < tymax) ? txmax : tymax;
					    
					    if (mEnnemy->getBox ().contains (tmin * mProjectile->getSpeed ())) {
					    
					    }
					
					
					// Si non, on regarde si il est dans sa conscience.
					    // Si oui, on le retire.
				}
			}
			
			return (mConsciousness->size () == 0);
		}
};

class LinkShouldAvoid : public lab::game::BehaviorLink {
	private:
		Ennemy* mEnnemy;
		std::list<Projectile*>* mProjectiles;
	
	public:
		LinkShouldAvoid (Ennemy* ennemy, int beha, std::list<Projectile*>* consciousness) : lab::game::BehaviorLink (beha) {
			mEnnemy = ennemy;
			mConsciousness = consciousness;
		}
		
		~LinkShouldAvoid () { }
		
		bool check () {
			// Tant que la conscience n'est pas "pleine"
			for (auto it = mProjectiles->begin (); it != mProjectiles->end (); it++) {
				// On regarde si ce projectile est dans le champ de vision de cet ennemi...
				// Puis on regarde si ce projectile a une trajectoire dangereuse pour cet ennemi, en fonction de l'erreur
				// possible d'évaluation.
				// Si oui, on l'ajoute dans sa conscience.
				if ( mViewField.contains ((*it)->getPosition ()) ) {
				
				}
			}
			
			return (mConsciousness->size () > 0);
		}
};

AvoidBehavior::AvoidBehavior (Ennemy* ennemy, lab::graphic::Drawable* drawable, 
							  const lab::math::Polygon<float>& view_field, int consciousness_size, int error_margin, 
							  int after_beha) : 
		: Behavior (ennemy, 1, drawable) {
		
	setLink (0, new LinkFinishAvoid (ennemy, after_beha, &mConsciousness));
	
	mViewField = view_field;
	mConsciousnessSize = consciousness_size;
	mErrorMargin = error_margin;
}

AvoidBehavior::~AvoidBehavior () {

}

void AvoidBehavior::cycle () {
	// On suppose qu'ici, il y a au moins un missile à éviter.
	
	// On détermine un lieu autour de l'ennemi qui permette à celui-ci de ne pas être inquiété par un des missiles dans
	// la conscience, en prenant en compte les erreurs que peut comettre l'ennemi.
	
	// On calcule l'accélération correspondante, en prenant en compte l'éventuelle erreur d'évaluation (modification 
	// aléatoire de l'accélération).
}
*/

}

