#ifndef _Bonus_hpp_
#define _Bonus_hpp_

#include <list>

#include "lab/Resources.hpp"
#include "lab/game/Entity.hpp"
#include "lab/math/Vector.hpp"
#include "lab/math/Box.hpp"
#include "lab/sound/Sample.hpp"

#include "Player.hpp"
#include "ennemies/Ennemy.hpp"

/****************************************************** Bonus *********************************************************/
class Bonus : public lab::game::Entity {
	protected:
		static Player* player;
		
		bool mToDelete;
		
		lab::sound::Sample* mSample;
		
	public:
		Bonus ( int mass,
				const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed,
				const lab::math::Box<float>& box,
				lab::graphic::Drawable* drawable,
				lab::sound::Sample* sample);
		
		~Bonus ();
		
		void cycle ();
		
		virtual void onTake ();
		
		bool isToDelete () const {return mToDelete;}
		
		static void setPlayer (Player* p) {Bonus::player = p;}
		
		lab::sound::Sample* getSample () const {return mSample;}
};

/****************************************************** Life **********************************************************/
class Life : public Bonus {
	public:
		Life (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources);
		
		~Life ();
		
		void onTake ();
};

/***************************************************** Shield *********************************************************/
class Shield : public Bonus {
	public:
		Shield (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources);
		
		~Shield ();
		
		void onTake ();
};

/*************************************************** Blue Life ********************************************************/
class BlueLife : public Bonus {
	public:
		BlueLife (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources);
		
		~BlueLife ();
		
		void onTake ();
};

/***************************************************** Weapon *********************************************************/
class Weapon : public Bonus {
	int mPower;

	public:
		Weapon (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources,
				int power);
		
		~Weapon ();
		
		void onTake ();
};

/****************************************************** Alarm *********************************************************/
class Alarm : public Bonus {
	    static float* spawnModifier;
	    static int*   spawnCount;
	    static long*  score;

	public:
		Alarm (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources);
		
		~Alarm ();
		
		void onTake ();
		
		static void setSpawnModifier(float *sm) {Alarm::spawnModifier = sm;}
		static void setSpawnCount(int* sc) {Alarm::spawnCount = sc;}
		static void setScore(long* sc) {Alarm::score = sc;}
};

/******************************************************* Bomb *********************************************************/
class Bomb : public Bonus {
	    static std::list<ennemy::Ennemy*>* ennemies;

	public:
		Bomb (const lab::math::Vector<float>& position, const lab::math::Vector<float>& speed, lab::Resources* resources);
		
		~Bomb ();
		
		void onTake ();
		
		static void setEnnemies(std::list<ennemy::Ennemy*>* e) {Bomb::ennemies = e;}
};

#endif

