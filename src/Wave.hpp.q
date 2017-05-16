#ifndef _Wave_hpp_
#define _Wave_hpp_

#include <boost/unordered_map.hpp>

#include "ennemies/Ennemy.hpp"

class Game;

class Wave {
	protected:
		boost::unordered_map<std::string, int> mSpawnProbabilityMap;
		
		static Game* game;
	
	public:
		Wave ();
		
		virtual ~Wave ();
		
		virtual void cycle ();
		
		virtual bool finished () const = 0;
		
		static void setGame ();
};

class ScoreWave {
	protected:
		int mScore;
	
	public:
		ScoreWave (int score);
		
		~ScoreWave ();
		
		bool finished () const;
};

class TimeWave {
	protected:
		int mDelay;
	
	public:
		TimeWave (int delay);
		
		~TimeWave ();
		
		void cycle ();
		
		bool finished () const;
};

class BossWave {
	protected:
		ennemy::Ennemy** mBoss;
	
	public:
		BossWave ();
		
		~BossWave ();
		
		void cycle ();
		
		bool finished () const;
		
		virtual ennemy::Ennemy* createBoss () = 0; 
		
};

#endif

