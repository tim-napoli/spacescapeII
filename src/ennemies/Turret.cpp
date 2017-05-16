#include "ennemies/Turret.hpp"
#include "ennemies/Behaviors.hpp"
#include "Projectile.hpp"

using namespace lab;
using namespace lab::math;

namespace ennemy {

ALLEGRO_BITMAP* Turret::projectile_sprite = NULL;

Turret::Turret (Vector<float> position, Vector<float> speed, float rotate_speed, int life, 
				ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* part_sprite) : 
			Ennemy (10, position, speed, Box<float> (0, 0, 24, 24), 0.0f,
					2, 
					life, life << 1, 40, 15, NULL,
					0.5f, 20.0f) {
	mAngle = 0.0f;
	mRotateSpeed = rotate_speed;
	setBehavior (0, new MoveBehavior (this,
							 		  new graphic::Sprite (Vector<int> (), 
							 								 Vector<int> (24, 24), 
							 								 Vector<int> (), 
							 								 0.0f, 50, 0, sprite),
				 					   Vector<float> (0.0f, 1 + rand () % 9), 
				 					   1
				 					  )
				);
	setBehavior (1, new ShootBehavior (	this, 1, 1, 
							 		  	new graphic::Sprite (Vector<int> (), 
							 								 Vector<int> (24, 24), 
							 								 Vector<int> (), 
							 								 0.0f, 50, 0, sprite),
							 			0
							 		 )
				);
	setDrawable (0);
	setCurrentBehavior (0);
}

Turret::~Turret () {

}

void Turret::update () {
	mAngle += mRotateSpeed;
	if (mAngle > 2 * ALLEGRO_PI) {
		mAngle -= 2 * ALLEGRO_PI;
	}
	
	//mAngle = mSpeed.angle (Vector<float> ()) - ALLEGRO_PI * 0.5;
	Ennemy::update ();
}

void Turret::cycle () throw (lab::Exception) {
	Ennemy::cycle ();
	
	if (mPosition.y > 540) {
		mToDelete = true;
	}
}

void Turret::shoot () {
	Ennemy::shoot ();

	Vector<float> position = Vector<float> (10.0f, 0.0f);
	Vector<float> speed = Vector<float> (4.0f, 0.0f);
	position.rotate (Vector<float> (0.0f, 0.0f), mAngle + ALLEGRO_PI * 0.5);
	position += mPosition + Vector<float> (12.0f, 12.0f);
	speed.rotate (Vector<float> (0.0f, 0.0f), mAngle + ALLEGRO_PI * 0.5);
	
	Ennemy::projectiles->push_front (new Projectile (2, position, speed, Box<float> (0, 0, 5, 5),
													 new graphic::Sprite (position, Vector<int> (5, 5), Vector<int> (),
													 			 0.0f, 49, 0, Turret::projectile_sprite),
													 5, 1, true, 0.3f, 8.0f, 10, al_map_rgba (150, 64, 16, 10)
													)
									);
}

Explosion* Turret::getExplosion () const {
	return new Explosion ( mPosition + (getDimensions () * 0.5) - Vector<float> (8, 8), mSpeed, 0.5f, 0.0f, 16, 10, 20, al_map_rgba (150, 64, 16, 10) );
}

}

