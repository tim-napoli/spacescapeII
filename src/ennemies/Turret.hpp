#ifndef _Turret_hpp_
#define _Turret_hpp_

#include <allegro5/allegro.h>

#include "ennemies/Ennemy.hpp"

namespace ennemy {

/***************************************************** Turret *********************************************************/
class Turret : public Ennemy {
	private:
		float mRotateSpeed;
		
		static ALLEGRO_BITMAP* projectile_sprite;

	public:
		Turret (lab::math::Vector<float> position, lab::math::Vector<float> speed, float rotate_speed, int life, 
				ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* part_sprite);
		
		~Turret ();
		
		void update ();
		
		void cycle () throw (lab::Exception);
		
		void shoot ();
		
		Explosion* getExplosion () const;
		
		static void setProjectileSprite (ALLEGRO_BITMAP* bmp) {projectile_sprite = bmp;}
};

}

#endif

