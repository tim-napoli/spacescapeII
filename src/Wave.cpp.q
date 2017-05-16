#include "Wave.hpp"

#include "ennemies/Turret.hpp"
#include "ennemies/Plane.hpp"
#include "Bonus.hpp"

namespace ennemy;

/******************************************************* Wave *********************************************************/
Game* Wave::game = NULL;

Wave::Wave () {

}

Wave::~Wave () {

}

void Wave::cycle () {
	for (auto it = mSpawnProbabilityMap.begin (); it != mSpawnProbabilityMap.end (); it++) {
		if (rand () % it->second == 0) {
			// Ennemis
			if (it->first.compare ("turret") == 0) {
				game->mEnnemies.push_front ( new Turret (Vector<float> (rand () % 938, -24), Vector<float> (0, 0), 
								   						 -0.1 + (rand () % 20) * 0.01, 10, 
								   			 			 game->mResources->getBitmap ("turret"), 
								   			 			 game->mResources->getBitmap ("star")
								   			 			) 
								   		   );
			}
			else if (it->first.compare ("red turret") == 0) {
				game->mEnnemies.push_front ( new Turret (Vector<float> (rand () % 938, -24), Vector<float> (0, 0), 
								   						 -0.1 + (rand () % 20) * 0.01, 20, 
								   			 			 game->mResources->getBitmap ("redturret"), 
								   			 			 game->mResources->getBitmap ("star")
								   			 			) 
								   		   );
			}
			else if (it->first.compare ("plane") == 0) {
				game->mEnnemies.push_front ( new Plane (Vector<float> (rand () % 912, -24), Vector<float> (0, 5.0), 
								   						game->mResources->getBitmap ("plane")
								   					   ) 
								   		   );
			}
			
			// Bonus
			else if (it->first.compare ("life") == 0) {
				game->mBonus.push_front (new Life (Vector<float> (0 + rand () % 928, -32), 
											 	   Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										 	 	   game->mResources
										    	  )
								  	    );
			}
			else if (it->first.compare ("weapon1") == 0 && game->mPlayer != NULL && game->mPlayer->getPower () < 2) {
				game->mBonus.push_front (new Weapon (Vector<float> (0 + rand () % 928, -32), 
											 	     Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										 	 	     game->mResources, 2
										    	    )
								  	    );
			}
		}
	}
}

void Wave::setGame (Game* g) {
	game = g;
}

/**************************************************** Score Wave ******************************************************/
ScoreWave::ScoreWave (int score) {
	mScore = score;
}

ScoreWave::~ScoreWave () {

}

bool ScoreWave::finished () const {
	return Wave::game->ScoreV >= mScore;
}

/**************************************************** Time Wave ******************************************************/
TimeWave::TimeWave (int delay) {
	mDelay = delay;
}

TimeWave::~TimeWave () {

}

void TimeWave::cycle () {
	Wave::cycle ();
	mDelay--;
}

bool TimeWave::finished () const {
	return mDelay <= 0;
}

/***************************************************** Boss Wave ******************************************************/
BossWave::BossWave () {
	mBoss = NULL;
}

BossWave::~BossWave () {

}

void BossWave::cycle () {
	Wave::cycle ();
	
	if (mBoss == NULL) {
		mBoss = &(Wave::game->mBoss);
		*mBoss = createBoss ();
	}
}

bool BossWave::finished () const {
	if (mBoss != NULL) {
		return *mBoss == NULL;
	}
	
	return false;
}

