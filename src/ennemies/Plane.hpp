#ifndef _ennemy_Plane_hpp_
#define _ennemy_Plane_hpp_

#include <allegro5/allegro.h>

#include "ennemies/Ennemy.hpp"

namespace ennemy {

/***************************************************** Plane **********************************************************/
class Plane : public Ennemy {
	private:
		static ALLEGRO_BITMAP* projectile_sprite;

	public:
		Plane (lab::math::Vector<float> position, lab::math::Vector<float> speed, ALLEGRO_BITMAP* sprite);
		
		~Plane ();
		
		void update ();
		
		void cycle () throw (lab::Exception);
		
		void shoot ();
		
		Explosion* getExplosion () const;
		
		static void setProjectileSprite (ALLEGRO_BITMAP* bmp) {projectile_sprite = bmp;}
};

}

#endif

