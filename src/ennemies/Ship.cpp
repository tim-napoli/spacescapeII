#include "ennemies/Ship.hpp"
#include "ennemies/Behaviors.hpp"

using namespace lab;
using namespace lab::math;
using namespace lab::graphic;

namespace ennemy {

ALLEGRO_BITMAP* Ship::projectile_sprite = NULL;

Ship::Ship (Vector<float> position, Vector<float> speed,
			  ALLEGRO_BITMAP* sprite) :
		Ennemy (40, position, speed, Box<float> (0, 0, 40, 54), 0.0f, 3,
				40, 100, 20, 10, NULL,
				0.4f, 8.0f) {
				
	setBehavior (0, new FollowBehavior (this, (*Ennemy::player)->getPositionAddress (), Vector<float> (-100 + rand () % 200, -100 - rand () % 200),
										new Sprite (Vector<int> (0, 0), Vector<int> (40, 54), Vector<int> (), 0.0f, 50, 0, sprite),
										2, 1)
				);
	
	setBehavior (1, new StopBehavior (this,
									  new Sprite (Vector<int> (0, 0), Vector<int> (40, 54), Vector<int> (), 0.0f, 50, 0, sprite),
									  0)
				);
				
	setBehavior (2, new ShootBehavior (this, 1, 1,
									   new Sprite (Vector<int> (0, 0), Vector<int> (40, 54), Vector<int> (), 0.0f, 50, 0, sprite),
									   0)
				);
	setDrawable (0);
	setCurrentBehavior (0);
}

Ship::~Ship () {

}

void Ship::update () {
	

	Ennemy::update ();
}

void Ship::cycle () throw (lab::Exception) {
	if (rand () % 25 == 0) {
		((FollowBehavior*) getBehavior (0))->setDifference (Vector<float> (-100 + rand () % 200, -200 - rand () % 200));
	} 
	
	if (*Ennemy::player == NULL && mPosition.y > 540) {
		mToDelete = true;
	}

	Ennemy::cycle ();
}

void Ship::shoot () {
	Ennemy::shoot ();

	Vector<float> position = mPosition + Vector<float> (12.0, 56.0);
	Vector<float> speed = Vector<float> (0.0, 7.0);
	Ennemy::projectiles->push_front (new Projectile (4, position, speed, Box<float> (0, 0, 12, 24),
													 new graphic::Sprite (position, Vector<int> (12, 24), Vector<int> (),
													 			 0.0f, 49, 0, Ship::projectile_sprite),
													 20, 1, true, 0.3f, 10.0f, 10, al_map_rgba (16, 16, 150, 16)
													)
									);
}

Explosion* Ship::getExplosion () const {
	return new Explosion ( mPosition + (getDimensions () * 0.5) - Vector<float> (10, 10), mSpeed, 0.6f, 0.0f, 20, 10, 20, al_map_rgba (16, 16, 150, 16) );
}

}

