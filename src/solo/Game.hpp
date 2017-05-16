/*!
 * Activité de jeu (un seul joueur).
 */
 
#ifndef _solo_Game_hpp_
#define _solo_Game_hpp_

#include <list>

#include "lab/Engine.hpp"
#include "lab/Resources.hpp"

#include "lab/graphic/Renderer.hpp"
#include "lab/graphic/ParticleSystem.hpp"
#include "lab/graphic/Text.hpp"
#include "lab/graphic/GVector.hpp"

#include "lab/sound/Stream.hpp"

#include "lab/activity/Activity.hpp"

#include "Background.hpp"
#include "Player.hpp"
#include "Projectile.hpp"

#include "ennemies/Turret.hpp"
#include "ennemies/Plane.hpp"
#include "ennemies/Ship.hpp"
#include "ennemies/Ship2.hpp"
#include "ennemies/Beetle.hpp"
#include "ennemies/Boss1.hpp"
#include "ennemies/Ennemy.hpp"

#include "Bonus.hpp"
#include "Explosion.hpp"

#include "LifeBar.hpp"
#include "ShieldBar.hpp"
#include "Score.hpp"
//#include "Wave.hpp"

class RestartTask;

class Game : public lab::activity::Activity {
	public:
		static const int STATE_PLAY 	= 0;
		static const int STATE_PAUSE 	= 1;
		static const int STATE_EXIT 	= 2;
		static const int STATE_SCORE	= 3;
		static const int STATE_GETNAME	= 4;

	private:
		int mState;	// L'état du jeu.
		bool mToRestart;
	
		// Données de fondation.
		lab::Resources* mResources;
		
		lab::graphic::Text* mPauseText;
		lab::graphic::Text* mQuitText;
		lab::graphic::ParticleSystem* mParticleSystemA; // Between the player, over the entities (zindex = 99).
		lab::graphic::ParticleSystem* mParticleSystemB; // Over the player, over the entities (zindex = 101).
		lab::graphic::ParticleSystem* mParticleSystemC; // Under the ennemies (zindex = 49).
		
		Background* mBackground;
		
		LifeBar* mLifeBar;
		ShieldBar* mShieldBar;
		
		lab::graphic::Text* mScoreText;
		Score* mScore;
		long mScoreV;
		lab::graphic::Text* mNameText;
		lab::graphic::Text* mNameSeizureText;
		bool mFinishNameSeizure;
		bool mIsWeaponBonus;
		
		float mSpawnModifier;
		int   mSpawnModifierCount;
		
		// Elements du monde.
		Player* mPlayer;
		std::list<Projectile*> mPlayerProjectiles;
		
		std::list<Projectile*> mEnnemiesProjectiles;
		std::list<ennemy::Ennemy*> mEnnemies;
		
		std::list<Bonus*> mBonus;
		
		std::list<Explosion*> mExplosions;
		
		// Musique
		lab::sound::Stream* mMusic;
	
	public:
	
		Game (lab::Engine* engine);
		
		~Game ();
		
		
		void initialize () throw (lab::Exception);
		
		void spawnNormal ();
		
		void update ();
		
		void cycle ();
		
		void render ();
		
		void shutdown ();
		
		void music ();
		
		void switchPause ();
		
		void switchExit ();
		
		void exit ();
		
		void start ();
		
		void stop ();
		
		void restart ();
		
		void switchToScoreScreen ();
		
		void finishNameSeizure ();
		
		void updateScore ();
		
	
		int getState () const {return mState;}
		
		// Friends
		friend class RestartTask;
		friend class NameSeizureTask;
		friend class FinishNameSeizureTask;
		
		friend class Wave;
		friend class ScoreWave;
		friend class TimeWave;
		friend class BossWave;
		
};

#endif


