#include "Bonus.hpp"

using namespace lab;
using namespace lab::game;
using namespace lab::math;
using namespace lab::graphic;
using namespace lab::sound;

/****************************************************** Bonus *********************************************************/
Player* Bonus::player = NULL;

Bonus::Bonus ( int mass,
			   const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed,
			   const lab::math::Box<float>& box,
			   Drawable* drawable,
			   Sample* sample) :
		Entity (mass, position, speed, box) {
	mToDelete = false;		
	mDrawable = drawable;
	Entity::renderer->addDrawable (mDrawable);
	syncronizeDrawable ();
	
	mSample = sample;
}

Bonus::~Bonus () {
	Entity::renderer->removeDrawable (mDrawable);
	delete mDrawable;
}

void Bonus::cycle () {
	if (mPosition.y > 540) {
		mToDelete = true;
	}
}

void Bonus::onTake () {
	mToDelete = true;
}

/****************************************************** Life **********************************************************/
Life::Life (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources) :
		Bonus (1, position, speed, Box<float> (0, 0, 24, 24),
			   new Sprite (Vector<int> (), Vector<int> (24, 24), Vector<int> (), 0.0f, 50, 0, 
			   			   resources->getBitmap ("life")), 
			   			   resources->getSample ("health")
			  ) {
	
}

Life::~Life () {

}

void Life::onTake () {
	Bonus::player->addLife (20);
	Bonus::onTake ();
}

/***************************************************** Shield *********************************************************/
Shield::Shield (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources) :
		Bonus (1, position, speed, Box<float> (0, 0, 24, 24),
			   new Sprite (Vector<int> (), Vector<int> (24, 24), Vector<int> (), 0.0f, 50, 0, 
			   			   resources->getBitmap ("shield")), 
			   			   resources->getSample ("health")
			  ) {
	
}

Shield::~Shield () {

}

void Shield::onTake () {
	Bonus::player->addShield (20);
	Bonus::onTake ();
}

/**************************************************** BlueLife ********************************************************/
BlueLife::BlueLife (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources) :
		Bonus (1, position, speed, Box<float> (0, 0, 24, 24),
			   new Sprite (Vector<int> (), Vector<int> (24, 24), Vector<int> (), 0.0f, 50, 0, 
			   			   resources->getBitmap ("life2")), 
			   			   resources->getSample ("health")
			  ) {
	
}

BlueLife::~BlueLife () {

}

void BlueLife::onTake () {
	Bonus::player->addLife (40);
	Bonus::onTake ();
}

/***************************************************** Weapon *********************************************************/
Weapon::Weapon (const lab::math::Vector<float>& position, const lab::math::Vector<float>& 
				speed, lab::Resources* resources, int power) :
		Bonus (1, position, speed, Box<float> (0, 0, 24, 24),
			   new Sprite (Vector<int> (), Vector<int> (24, 24), Vector<int> (), 0.0f, 50, 0, 
			   			   resources->getBitmap ("weapon")),
			   			   resources->getSample ("weapon")
			  ) {
	mPower = power;	
}

Weapon::~Weapon () {

}

void Weapon::onTake () {
	if (Bonus::player->getPower () < mPower) {
		Bonus::player->setPower (mPower);
	}
	Bonus::onTake ();
}

/****************************************************** Alarm *********************************************************/
float* Alarm::spawnModifier = NULL;
int*   Alarm::spawnCount = NULL;
long*  Alarm::score = NULL;

Alarm::Alarm (const lab::math::Vector<float>& position, const lab::math::Vector<float>& 
				speed, lab::Resources* resources) :
		Bonus (1, position, speed, Box<float> (0, 0, 24, 24),
			   new Sprite (Vector<int> (), Vector<int> (24, 24), Vector<int> (), 0.0f, 50, 0, 
			   			   resources->getBitmap ("alarm")),
			   			   resources->getSample ("alarm")
			  ) {

}

Alarm::~Alarm () {

}

void Alarm::onTake () {
	*Alarm::spawnModifier *= 0.33;
	*Alarm::spawnCount += 375;
	*Alarm::score += 1000;
	Bonus::onTake ();
}

/******************************************************* Bomb *********************************************************/
std::list<ennemy::Ennemy*>* Bomb::ennemies = NULL;

Bomb::Bomb (const lab::math::Vector<float>& position, const lab::math::Vector<float>& 
				speed, lab::Resources* resources) :
		Bonus (1, position, speed, Box<float> (0, 0, 28, 28),
			   new Sprite (Vector<int> (), Vector<int> (28, 28), Vector<int> (), 0.0f, 50, 0, 
			   			   resources->getBitmap ("bomb")),
			   			   resources->getSample ("bigexp")
			  ) {

}

Bomb::~Bomb () {

}

void Bomb::onTake () {
	
	for (auto it = Bomb::ennemies->begin (); it != Bomb::ennemies->end (); it++) {
	    (*it)->addDamages(100);
	}
	Bonus::player->addDamages(32);
	
	Bonus::onTake ();
}

