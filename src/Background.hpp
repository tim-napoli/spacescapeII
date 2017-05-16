#include <list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "lab/graphic/Drawable.hpp"
#include "lab/graphic/Sprite.hpp"

struct star {
	float x, y;
	float speed;
	int base_color, color, color_amp;
	float radius;
	float counter, counter_speed;
};

class Background : public lab::graphic::Drawable {
	star mStars [50];
	int mOffset;
	ALLEGRO_BITMAP* mBackground;
	
	public:
		Background (ALLEGRO_BITMAP* background);
		
		~Background ();
		
		void update ();
		
		void draw () const;
};

