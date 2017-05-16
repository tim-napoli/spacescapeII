#include "Projectile.hpp"

using namespace lab;
using namespace lab::math;
using namespace lab::graphic;
using namespace lab::game;

Projectile::Projectile (int mass, 
						const Vector<float>& position, 
						const Vector<float>& speed,
						const lab::math::Box<float>& box,
						lab::graphic::Sprite* drawable,
						int damages, int life, bool main,
						float expl_speed, float expl_size, int expl_life, ALLEGRO_COLOR expl_color) :
		Entity (mass, position, speed, box) {
	mDamages = damages;
	mDrawable = drawable;
	Entity::renderer->addDrawable (mDrawable);	
	mToDelete = false;
	
	mLife = life;
	mExplSpeed = expl_speed;
	mExplSize = expl_size;
	mExplLife = expl_life;
	mMain = main;
	
	mExplColor = expl_color;
}

Projectile::~Projectile () {
	Entity::renderer->removeDrawable (mDrawable);
	delete mDrawable;
}

void Projectile::update () {
	physic::Object::update ();
}

void Projectile::cycle () {

}

void Projectile::onBoom () {
    
}

Explosion* Projectile::getExplosion () const {
	return new Explosion ( mPosition + (getDimensions () * 0.5) - Vector<float> (mExplSize, mExplSize), mSpeed * 0.4, mExplSpeed, 0.0f, mExplSize, 10, mExplLife, mExplColor );
}

