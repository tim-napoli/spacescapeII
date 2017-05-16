#ifndef _LifeBar_hpp_
#define _LifeBar_hpp_

#include <allegro5/allegro.h>

#include "lab/Resources.hpp"
#include "lab/graphic/Drawable.hpp"
#include "lab/math/Vector.hpp"

#include "Player.hpp"


class LifeBar : public lab::graphic::Drawable {
	private:
		Player** mPlayer;
		ALLEGRO_BITMAP *mBackground, *mForground;
	
	public:
		LifeBar (const lab::math::Vector<int>& position, Player** player, lab::Resources* resources);
		
		~LifeBar ();
		
		void draw () const;
};

#endif

