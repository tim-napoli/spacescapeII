#ifndef _game_Explosable_hpp_
#define _game_Explosable_hpp_

#include "Explosion.hpp"

namespace game {

class Explosable {
	public:
		virtual Explosion* getExplosion () const = 0;
};

}

#endif

