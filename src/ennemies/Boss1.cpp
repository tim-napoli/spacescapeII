#include "ennemies/Boss1.hpp"
#include "ennemies/Behaviors.hpp"

using namespace lab;
using namespace lab::math;
using namespace lab::graphic;

namespace ennemy {

ALLEGRO_BITMAP* Boss1::projectile_sprite = NULL;

Boss1::Boss1 (Vector<float> position, Vector<float> speed,
			  ALLEGRO_BITMAP* sprite) :
		Ennemy (1000, position, speed, Box<float> (0, 0, 238, 136), 0.0f, 3,
				2000, 2000, 10, 65, NULL,
				0.4f, 8.0f) {
				
	setBehavior (0, new FollowBehavior (this, (*Ennemy::player)->getPositionAddress (), Vector<float> (-500 + rand () % 400, -800),
										new Sprite (Vector<int> (0, 0), Vector<int> (238, 136), Vector<int> (), 0.0f, 50, 0, sprite),
										2, 1)
				);
	
	setBehavior (1, new StopBehavior (this,
									  new Sprite (Vector<int> (0, 0), Vector<int> (238, 136), Vector<int> (), 0.0f, 50, 0, sprite),
									  0)
				);
	
	setBehavior (2, new ShootBehavior (this, 1, 1,
									   new Sprite (Vector<int> (0, 0), Vector<int> (238, 136), Vector<int> (), 0.0f, 50, 0, sprite),
									   0)
				);
				
	setDrawable (0);
	setCurrentBehavior (0);
}

Boss1::~Boss1 () {

}

void Boss1::update () {
	

	Ennemy::update ();
}

void Boss1::cycle () throw (lab::Exception) {
	if (rand () % 25 == 0) {
		((FollowBehavior*) getBehavior (0))->setDifference (Vector<float> (-200 + rand () % 200, -500 + rand() % 150));
	} 
	
	if (*Ennemy::player == NULL && mPosition.y > 540) {
		mToDelete = true;
	}
	
	Ennemy::cycle ();
}

void Boss1::shoot () {
	Ennemy::shoot ();
	
	if (rand() % 2 == 0) {
	    Vector<float> position = mPosition + Vector<float> (24.0, 97.0);
	    Vector<float> speed = Vector<float> (0.0, 5 + rand () % 5);
	    Ennemy::projectiles->push_front (new Projectile (4, position, speed, Box<float> (0, 0, 5, 5),
													 new graphic::Sprite (position, Vector<int> (5, 5), Vector<int> (),
													 			          0.0f, 49, 0, Boss1::projectile_sprite),
													 10, 1, true, 0.3f, 10.0f, 10, al_map_rgba (150, 16, 16, 16)
													)
									);
	}
	if (rand() % 2 == 0) {
	    Vector<float> position = mPosition + Vector<float> (34.0, 109.0);
	    Vector<float> speed = Vector<float> (0.0, 5 + rand () % 5);
	    Ennemy::projectiles->push_front (new Projectile (4, position, speed, Box<float> (0, 0, 5, 5),
													 new graphic::Sprite (position, Vector<int> (5, 5), Vector<int> (),
													 			          0.0f, 49, 0, Boss1::projectile_sprite),
													 10, 1, true, 0.3f, 10.0f, 10, al_map_rgba (150, 16, 16, 16)
													)
									);
	}
	if (rand() % 2 == 0) {
	    Vector<float> position = mPosition + Vector<float> (45.0, 104.0);
	    Vector<float> speed = Vector<float> (0.0, 5 + rand () % 5);
	    Ennemy::projectiles->push_front (new Projectile (4, position, speed, Box<float> (0, 0, 5, 5),
													 new graphic::Sprite (position, Vector<int> (5, 5), Vector<int> (),
													 			          0.0f, 49, 0, Boss1::projectile_sprite),
													 10, 1, true, 0.3f, 10.0f, 10, al_map_rgba (150, 16, 16, 16)
													)
									);
	}
	
	if (rand() % 2 == 0) {
	    Vector<float> position = mPosition + Vector<float> (192.0, 104.0);
	    Vector<float> speed = Vector<float> (0.0, 5 + rand () % 5);
	    Ennemy::projectiles->push_front (new Projectile (4, position, speed, Box<float> (0, 0, 5, 5),
													 new graphic::Sprite (position, Vector<int> (5, 5), Vector<int> (),
													 			          0.0f, 49, 0, Boss1::projectile_sprite),
													 10, 1, true, 0.3f, 10.0f, 10, al_map_rgba (150, 16, 16, 16)
													)
									);
	}
	if (rand() % 2 == 0) {
	    Vector<float> position = mPosition + Vector<float> (204.0, 109.0);
	    Vector<float> speed = Vector<float> (0.0, 5 + rand () % 5);
	    Ennemy::projectiles->push_front (new Projectile (4, position, speed, Box<float> (0, 0, 5, 5),
													 new graphic::Sprite (position, Vector<int> (5, 5), Vector<int> (),
													 			          0.0f, 49, 0, Boss1::projectile_sprite),
													 10, 1, true, 0.3f, 10.0f, 10, al_map_rgba (150, 16, 16, 16)
													)
									);
	}
	if (rand() % 2 == 0) {
	    Vector<float> position = mPosition + Vector<float> (212.0, 97.0);
	    Vector<float> speed = Vector<float> (0.0, 5 + rand () % 5);
	    Ennemy::projectiles->push_front (new Projectile (4, position, speed, Box<float> (0, 0, 5, 5),
													 new graphic::Sprite (position, Vector<int> (5, 5), Vector<int> (),
													 			          0.0f, 49, 0, Boss1::projectile_sprite),
													 10, 1, true, 0.3f, 10.0f, 10, al_map_rgba (150, 16, 16, 16)
													)
									);
	}
}

Explosion* Boss1::getExplosion () const {
	return new Explosion ( mPosition + (getDimensions () * 0.5) - Vector<float> (10, 10), mSpeed, 0.6f, 0.0f, 80, 10, 20, al_map_rgba (200, 16, 16, 16) );
}

}

