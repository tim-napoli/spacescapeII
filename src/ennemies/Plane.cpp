#include "ennemies/Plane.hpp"
#include "ennemies/Behaviors.hpp"

using namespace lab;
using namespace lab::math;
using namespace lab::graphic;

namespace ennemy {

ALLEGRO_BITMAP* Plane::projectile_sprite = NULL;

Plane::Plane (Vector<float> position, Vector<float> speed,
			  ALLEGRO_BITMAP* sprite) :
		Ennemy (20, position, speed, Box<float> (0, 0, 48, 24), 0.0f, 3,
				20, 60, 10, 5, NULL,
				0.5f, 10.0f) {
				
	setBehavior (0, new FollowBehavior (this, (*Ennemy::player)->getPositionAddress (), Vector<float> (-100 + rand () % 200, -100 - rand () % 200),
										new Sprite (Vector<int> (0, 0), Vector<int> (48, 24), Vector<int> (), 0.0f, 50, 0, sprite),
										2, 1)
				);
	
	setBehavior (1, new StopBehavior (this,
									  new Sprite (Vector<int> (0, 0), Vector<int> (48, 24), Vector<int> (), 0.0f, 50, 0, sprite),
									  0)
				);
				
	setBehavior (2, new ShootBehavior (this, 1, 1,
									   new Sprite (Vector<int> (0, 0), Vector<int> (48, 24), Vector<int> (), 0.0f, 50, 0, sprite),
									   0)
				);
	setDrawable (0);
	setCurrentBehavior (0);
}

Plane::~Plane () {

}

void Plane::update () {
	

	Ennemy::update ();
}

void Plane::cycle () throw (lab::Exception) {
	if (rand () % 25 == 0) {
		((FollowBehavior*) getBehavior (0))->setDifference (Vector<float> (-100 + rand () % 200, -150 - rand () % 200));
	} 
	
	if (*Ennemy::player == NULL && mPosition.y > 540) {
		mToDelete = true;
	}

	Ennemy::cycle ();
}

void Plane::shoot () {
	Ennemy::shoot ();

	Vector<float> position = mPosition + Vector<float> (22.0, 20.0);
	Vector<float> speed = Vector<float> (0.0, 7.0);
	Ennemy::projectiles->push_front (new Projectile (2, position, speed, Box<float> (0, 0, 6, 6),
													 new graphic::Sprite (position, Vector<int> (6, 6), Vector<int> (),
													 			 0.0f, 49, 0, Plane::projectile_sprite),
													 5, 1, true, 0.3f, 8.0f, 10, al_map_rgba (150, 64, 16, 10)
													)
									);
}

Explosion* Plane::getExplosion () const {
	return new Explosion ( mPosition + (getDimensions () * 0.5) - Vector<float> (10, 10), mSpeed, 0.5f, 0.0f, 20, 10, 20, al_map_rgba (200, 64, 32, 10) );
}

}
