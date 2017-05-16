#ifndef _ennemy_Ship2_hpp_
#define _ennemy_Ship2_hpp_

#include <allegro5/allegro.h>

#include "ennemies/Ennemy.hpp"

namespace ennemy {

/***************************************************** Ship ***********************************************************/
class Ship2 : public Ennemy {
	private:
		static ALLEGRO_BITMAP* projectile_sprite;

	public:
		Ship2 (lab::math::Vector<float> position, lab::math::Vector<float> speed, ALLEGRO_BITMAP* sprite);
		
		~Ship2 ();
		
		void update ();
		
		void cycle () throw (lab::Exception);
		
		void shoot ();
		
		Explosion* getExplosion () const;
		
		static void setProjectileSprite (ALLEGRO_BITMAP* bmp) {projectile_sprite = bmp;}
};

}

#endif

