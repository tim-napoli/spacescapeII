#ifndef _ennemy_Boss1_hpp_
#define _ennemy_Boss1_hpp_

#include <allegro5/allegro.h>

#include "ennemies/Ennemy.hpp"

namespace ennemy {

/***************************************************** Ship ***********************************************************/
class Boss1 : public Ennemy {
	private:
		static ALLEGRO_BITMAP* projectile_sprite;

	public:
		Boss1 (lab::math::Vector<float> position, lab::math::Vector<float> speed, ALLEGRO_BITMAP* sprite);
		
		~Boss1 ();
		
		void update ();
		
		void cycle () throw (lab::Exception);
		
		void shoot ();
		
		Explosion* getExplosion () const;
		
		static void setProjectileSprite (ALLEGRO_BITMAP* bmp) {Boss1::projectile_sprite = bmp;}
};

}

#endif

