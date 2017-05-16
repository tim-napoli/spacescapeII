#ifndef _ennemy_Ship_hpp_
#define _ennemy_Ship_hpp_

#include <allegro5/allegro.h>

#include "ennemies/Ennemy.hpp"

namespace ennemy {

/***************************************************** Ship ***********************************************************/
class Ship : public Ennemy {
	private:
		static ALLEGRO_BITMAP* projectile_sprite;

	public:
		Ship (lab::math::Vector<float> position, lab::math::Vector<float> speed, ALLEGRO_BITMAP* sprite);
		
		~Ship ();
		
		void update ();
		
		void cycle () throw (lab::Exception);
		
		void shoot ();
		
		Explosion* getExplosion () const;
		
		static void setProjectileSprite (ALLEGRO_BITMAP* bmp) {projectile_sprite = bmp;}
};

}

#endif

