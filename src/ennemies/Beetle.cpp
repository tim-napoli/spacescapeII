#include "ennemies/Beetle.hpp"
#include "ennemies/Behaviors.hpp"

using namespace lab;
using namespace lab::math;
using namespace lab::graphic;

namespace ennemy {

Beetle::Beetle (Vector<float> position, Vector<float> speed,
			    ALLEGRO_BITMAP* sprite) :
		Ennemy (50, position, speed, Box<float> (0, 0, 26, 26), 0.0f, 3,
				1, 20, 0, 0, NULL,
				0.6f, 12.0f) {
				
	setBehavior (0, new FollowBehavior (this, (*Ennemy::player)->getPositionAddress (), Vector<float> (-50 + rand () % 100, -50 - rand () % 100),
										new Sprite (Vector<int> (0, 0), Vector<int> (26, 26), Vector<int> (), 0.0f, 50, 0, sprite),
										2, 2)
				);
	
	setBehavior (1, new StopBehavior (this,
									  new Sprite (Vector<int> (0, 0), Vector<int> (26, 26), Vector<int> (), 0.0f, 50, 0, sprite),
									  2)
				);
				
	setBehavior (2, new FollowBehavior (this, (*Ennemy::player)->getPositionAddress (), Vector<float> (0, 0),
										new Sprite (Vector<int> (0, 0), Vector<int> (26, 26), Vector<int> (), 0.0f, 50, 0, sprite),
										0, 1)
				);

	setDrawable (0);
	setCurrentBehavior (0);
}

Beetle::~Beetle () {

}

void Beetle::update () {
	Ennemy::update ();
}

void Beetle::cycle () throw (lab::Exception) {
	if (rand () % 25 == 0) {
		((FollowBehavior*) getBehavior (0))->setDifference (Vector<float> (-100 + rand () % 200, -100 - rand () % 200));
	}
	
	if (*Ennemy::player == NULL && mPosition.y > 540) {
		mToDelete = true;
	}

    mAngle = mAcceleration.angle() + 3.14159365 * 0.5;

	Ennemy::cycle ();
}

void Beetle::shoot () {

}

Explosion* Beetle::getExplosion () const {
	return new Explosion ( mPosition + (getDimensions () * 0.5) - Vector<float> (5, 5), mSpeed, 0.6f, 0.0f, 10, 10, 20, al_map_rgba (16, 150, 16, 16) );
}

}

