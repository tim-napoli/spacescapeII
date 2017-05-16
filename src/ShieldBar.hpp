#ifndef _ShieldBar_hpp_
#define _ShieldBar_hpp_

#include <allegro5/allegro.h>

#include "lab/Resources.hpp"
#include "lab/graphic/Drawable.hpp"
#include "lab/math/Vector.hpp"

#include "Player.hpp"


class ShieldBar : public lab::graphic::Drawable {
	private:
		Player** mPlayer;
		ALLEGRO_BITMAP *mBackground, *mForground;
	
	public:
		ShieldBar (const lab::math::Vector<int>& position, Player** player, lab::Resources* resources);
		
		~ShieldBar ();
		
		void draw () const;
};

#endif

