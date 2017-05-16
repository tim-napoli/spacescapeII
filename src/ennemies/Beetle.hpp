#ifndef _ennemy_Beetle_hpp_
#define _ennemy_Beetle_hpp_

#include <allegro5/allegro.h>

#include "ennemies/Ennemy.hpp"

namespace ennemy {

/**************************************************** Beetle **********************************************************/
class Beetle : public Ennemy {
	public:
		Beetle (lab::math::Vector<float> position, lab::math::Vector<float> speed, ALLEGRO_BITMAP* sprite);
		
		~Beetle ();
		
		void update ();
		
		void cycle () throw (lab::Exception);
		
		void shoot ();
		
		Explosion* getExplosion () const;
};

}

#endif

