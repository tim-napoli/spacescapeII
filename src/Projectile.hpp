#ifndef _Projectile_hpp_
#define _Projectile_hpp_

#include <allegro5/allegro.h>

#include "lab/Resources.hpp"
#include "lab/game/Entity.hpp"
#include "lab/graphic/Sprite.hpp"
#include "lab/graphic/ParticleEmitter.hpp"
#include "lab/math/Vector.hpp"
#include "lab/math/Box.hpp"

#include "Explosion.hpp"

class Projectile : public lab::game::Entity {
	private:
		int mDamages;
		bool mToDelete;
		//static ParticleEmitter* particles;
		
		float mExplSpeed;
		float mExplSize;
		int mExplLife;
		ALLEGRO_COLOR mExplColor;
		
		int mLife;
		bool mMain; // To know if this projectile is a main one.
	
	public:
		Projectile (int mass, 
					const lab::math::Vector<float>& position, 
					const lab::math::Vector<float>& speed,
					const lab::math::Box<float>& box,
					lab::graphic::Sprite* drawable,
					int damages, int life, bool main,
					float expl_speed, float expl_size, int expl_life, ALLEGRO_COLOR expl_color);
		
		~Projectile ();
		
		int getDamages () const {return mDamages;}
		
		void update ();
		
		virtual void cycle ();
		
		virtual void onBoom ();
		
		void setToDelete (bool b) {mToDelete = b;}
		
		bool isToDelete () const {return mToDelete;}
		
		bool isDead () const {return mLife <= 0;}
		
		bool isMain() const {return mMain;}
		
		void addDamages (int d) {mLife -= d;}
		
		virtual Explosion* getExplosion () const;
};

#endif

