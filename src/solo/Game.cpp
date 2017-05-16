#include <allegro5/allegro.h>

#include "lab/math/Vector.hpp"
#include "solo/Game.hpp"
#include "solo/Tasks.hpp"

#include "lab/game/BehavioredEntity.hpp"

using namespace lab;
using namespace lab::activity;
using namespace lab::graphic;
using namespace lab::math;
using namespace lab::game;

/***************************************************** Game ***********************************************************/
Game::Game (Engine* engine) : Activity (engine) {
	mMusic = NULL;
	mScore = NULL;
	mNameText = NULL;
	mNameSeizureText = NULL;
	mPlayer = NULL;
	mToRestart = false;
	mFinishNameSeizure = false;
}

Game::~Game () {

}

/************************************************** Initialize ********************************************************/
void Game::initialize () throw (lab::Exception) {
	Activity::initialize ();
	
	mState = Game::STATE_PLAY;
	
	// Ouverture des ressources
	mResources = new Resources (getEngine ()->getResourcesPath () + "data/");
	try {
		mResources->load (getEngine ()->getResourcesPath () + "data/data.cfg");
	} catch (const Exception& exception) {
		throw Exception (0, "Game::initialize error : Cannot load datas :\n\t" + exception.getMessage ());
	}
	
	// Données de fondation
	mRenderer = new Renderer (Vector<int> (960, 540), getEngine ()->getVideo (), false);
	Entity::setRenderer (mRenderer); // Ne pas oublier ceci !
	
	mPauseText = new Text (Vector<int> (480, 270), Vector<int> (), 0.0f, 103, mResources->getFont ("font_normal"), 
						   al_map_rgb (0, 0, 175), "Pause", Text::ALIGN_CENTER);
	mQuitText = new Text (Vector<int> (480, 270), Vector<int> (), 0.0f, 103, mResources->getFont ("font_normal"), 
					  	  al_map_rgb (255, 255, 255), "Do you really want to quit (y/n) ?", Text::ALIGN_CENTER);
	
	mScoreText = new Text (Vector<int> (10, 30), Vector<int> (), 0.0f, 103, mResources->getFont ("font_little"),
						   al_map_rgb (34, 68, 192), "Score : 0", Text::ALIGN_LEFT);
	mRenderer->addDrawable (mScoreText);
	
	mParticleSystemA = new ParticleSystem (Vector<int> (960, 540), 99, 200);
	mRenderer->addDrawable (mParticleSystemA);
	mParticleSystemB = new ParticleSystem (Vector<int> (960, 540), 101, 400);
	mRenderer->addDrawable (mParticleSystemB);
	mParticleSystemC = new ParticleSystem (Vector<int> (960, 540), 49, 200);
	mRenderer->addDrawable (mParticleSystemC);
	
	mBackground = new Background (mResources->getBitmap ("background"));
	mRenderer->addDrawable (mBackground);
	
	// Données statiques à attacher.
	ennemy::Turret::setProjectileSprite (mResources->getBitmap ("tur_proj"));
	ennemy::Plane::setProjectileSprite (mResources->getBitmap ("tur_proj"));
	ennemy::Ship::setProjectileSprite (mResources->getBitmap ("blueproj2"));
	ennemy::Ship2::setProjectileSprite (mResources->getBitmap ("pproj2"));
	ennemy::Boss1::setProjectileSprite (mResources->getBitmap ("tur_proj"));
	ennemy::Ennemy::setProjectiles (&mEnnemiesProjectiles);
	ennemy::Ennemy::setParticleSystem (mParticleSystemC);
	
	Alarm::setSpawnModifier(&mSpawnModifier);
	Alarm::setSpawnCount(&mSpawnModifierCount);
	Alarm::setScore(&mScoreV);
	Bomb::setEnnemies(&mEnnemies);
	
	Explosion::setSprite (mResources->getBitmap ("star"));
	Explosion::setParticleSystem (mParticleSystemB);
	
	GameTask::setGame (this);


	// Initialise les données du jeu.
	start ();
	
	// And music !
	music ();
}

/***************************************************** Udate **********************************************************/
void Game::spawnNormal() {
    if (rand () % (int) (25 * mSpawnModifier) == 0) {
		mEnnemies.push_front ( new ennemy::Turret (Vector<float> (rand () % 938, -24), Vector<float> (0, 0), 
							   -0.1 + (rand () % 20) * 0.01, 10, 
							   mResources->getBitmap ("turret"), mResources->getBitmap ("star")) );
	}
	if (mScoreV >= 1000 && rand () % (int) (50 * mSpawnModifier) == 0) {
		mEnnemies.push_front ( new ennemy::Turret (Vector<float> (rand () % 938, -24), Vector<float> (0, 0), 
								-0.1 + (rand () % 20) * 0.01, 20, 
								mResources->getBitmap ("redturret"), mResources->getBitmap ("star")) );
	}
	if (mScoreV >= 2000 && rand () % (int) (300 * mSpawnModifier) == 0) {
		mEnnemies.push_front ( new ennemy::Plane (Vector<float> (rand () % 912, -24), Vector<float> (0, 5.0), 
							   mResources->getBitmap ("plane")) );
	}
	if (mScoreV >= 4000 && rand () % (int) (450 * mSpawnModifier) == 0) {
		mEnnemies.push_front ( new ennemy::Ship (Vector<float> (rand () % 912, -24), Vector<float> (0, 5.0), 
							   mResources->getBitmap ("ship")) );
	}
	if (mScoreV >= 8000 && rand () % (int) (150 * mSpawnModifier) == 0) {
		mEnnemies.push_front ( new ennemy::Beetle (Vector<float> (rand () % 912, -24), Vector<float> (0, 5.0), 
							   mResources->getBitmap ("scarab")) );
		mEnnemies.push_front ( new ennemy::Beetle (Vector<float> (rand () % 912, -24), Vector<float> (0, 5.0), 
							   mResources->getBitmap ("scarab")) );
		mEnnemies.push_front ( new ennemy::Beetle (Vector<float> (rand () % 912, -24), Vector<float> (0, 5.0), 
							   mResources->getBitmap ("scarab")) );
	}
	if (mScoreV >= 16000 && rand () % (int) (500 * mSpawnModifier) == 0) {
		mEnnemies.push_front ( new ennemy::Ship2 (Vector<float> (rand () % 912, -24), Vector<float> (0, 5.0), 
							   mResources->getBitmap ("ship2")) );
	}
}

void Game::update () {
	if (mToRestart) {
		restart ();
	}
	
	if (mPlayer == NULL && mScore == NULL) {
		switchToScoreScreen ();
	}
	
	if (mFinishNameSeizure) {
		finishNameSeizure ();
	}

	if (mState == Game::STATE_PLAY || mState == Game::STATE_SCORE || mState == Game::STATE_GETNAME) {
		if (mPlayer != NULL) {
			if (mPlayer->getLife () <= 0) {
				mExplosions.push_front (mPlayer->getExplosion ());
				mResources->getSample ("bigexp")->play (1.5, 0.0, 1.0, false);
				delete mPlayer;
				mPlayer = NULL;
			}
			else {
				mPlayer->update ();
				mPlayer->syncronizeDrawable ();
			
				if (mPlayer->shooting ()) {
					mPlayer->shoot (&mPlayerProjectiles);
				}
			}
		}
		
		
		// Ennemies
		if (mScoreV < 8000) {
		    spawnNormal();
		}
		else if (mEnnemies.size () == 0 && mScoreV < 10000 && mPlayer != NULL) {
		    mEnnemies.push_front ( new ennemy::Boss1 (Vector<float> (rand () % 912, -120), Vector<float> (0, 5.0), 
								       mResources->getBitmap ("boss1")) );
		}
		else if (mScoreV >= 10000) {
		    spawnNormal();
		}
		
		for (auto it = mEnnemies.begin (); it != mEnnemies.end (); it++) {
			if ((*it)->toDelete ()) {
				delete *it;
				it = mEnnemies.erase (it);
				it--;
			}
			else if ((*it)->isDead ()) {
				mExplosions.push_front ((*it)->getExplosion ());
				mScoreV += (*it)->getScore ();
				updateScore ();
				
				if (mPlayer != NULL) {
					float sound_intensity = 1.5f - (((*it)->getPosition () - mPlayer->getPosition ()).length ()) / 540.0f;
					mResources->getSample ("litexp")->play (sound_intensity, 0.0, 1.0, false);
				}
				
				delete *it;
				it = mEnnemies.erase (it);
				it--;
			}
			else {
				if ((*it)->mustShoot ()) {
					(*it)->shoot ();
				}
				(*it)->update ();
				(*it)->syncronizeDrawable ();
			}
		}
		
		// Player projectiles
		for (auto it = mPlayerProjectiles.begin (); it != mPlayerProjectiles.end (); it++) {
			if ((*it)->getPosition ().x < 0 || (*it)->getPosition ().x > 960 || 
				(*it)->getPosition ().y < 0 || (*it)->getPosition ().y > 540 ||
				(*it)->isToDelete ()) {
				delete *it;
				it = mPlayerProjectiles.erase (it);
				it--;
			}
			else if ((*it)->isDead ()) {
				mExplosions.push_front ((*it)->getExplosion ());
				delete *it;
				it = mPlayerProjectiles.erase (it);
				it--;
			}
			else {
				(*it)->update ();
				(*it)->syncronizeDrawable ();
			}
		}
		
		// Ennemies projectiles
		for (auto it = mEnnemiesProjectiles.begin (); it != mEnnemiesProjectiles.end (); it++) {
			if ((*it)->getPosition ().x < 0 || (*it)->getPosition ().x > 960 || 
				(*it)->getPosition ().y < 0 || (*it)->getPosition ().y > 540 ||
				(*it)->isToDelete ()) {
				delete *it;
				it = mEnnemiesProjectiles.erase (it);
				it--;
			}
			else if ((*it)->isDead ()) {
				mExplosions.push_front ((*it)->getExplosion ());
				delete *it;
				it = mEnnemiesProjectiles.erase (it);
				it--;
			}
			else {
				(*it)->update ();
				(*it)->syncronizeDrawable ();
			}
		}
		
		// Bonus
		if (rand () % 750 == 0) {
			mBonus.push_front (new Life (Vector<float> (0 + rand () % 928, -32), Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										 mResources)
							  );
		}
		if (rand () % 1500 == 0) {
			mBonus.push_front (new BlueLife (Vector<float> (0 + rand () % 928, -32), Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										 mResources)
							  );
		}
		
		if (rand () % 750 == 0) {
			mBonus.push_front (new Shield (Vector<float> (0 + rand () % 928, -32), Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										 mResources)
							  );
		}
		
		if (rand () % 2000 == 0) {
			mBonus.push_front (new Alarm (Vector<float> (0 + rand () % 928, -32), Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										 mResources)
							  );
		}
		
		if (rand () % 2000 == 0) {
			mBonus.push_front (new Bomb (Vector<float> (0 + rand () % 928, -32), Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										 mResources)
							  );
		}
		
		if (mPlayer != NULL && mPlayer->getPower () < 2 && mScoreV >= 3000 && !mIsWeaponBonus) {
			mBonus.push_front (new Weapon (Vector<float> (0 + rand () % 928, -32), Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										   mResources, mPlayer->getPower () + 1)
							  );
            mIsWeaponBonus = true;
		}
		
		if (mPlayer != NULL && mPlayer->getPower () < 3 && mScoreV >= 6000  && !mIsWeaponBonus) {
			mBonus.push_front (new Weapon (Vector<float> (0 + rand () % 928, -32), Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										   mResources, mPlayer->getPower () + 1)
							  );
		    mIsWeaponBonus = true;
		}
		
		if (mPlayer != NULL && mPlayer->getPower () < 4 && mScoreV >= 12000 &&  !mIsWeaponBonus) {
			mBonus.push_front (new Weapon (Vector<float> (0 + rand () % 928, -32), Vector<float> (0.0f, 1.0f + (rand () % 50) * 0.1),
										   mResources, mPlayer->getPower () + 1)
							  );
			mIsWeaponBonus = true;
		}
		
		for (auto it = mBonus.begin (); it != mBonus.end (); it++) {
			if ((*it)->isToDelete ()) {
				if (dynamic_cast<Weapon*>(*it) != NULL) {
				    mIsWeaponBonus = false;
				}
				delete *it;
				it = mBonus.erase (it);
				it--;
			}
			else {
				(*it)->update ();
				(*it)->cycle ();
				(*it)->syncronizeDrawable ();
			}
		}
		
		// Explosions
		for (auto it = mExplosions.begin (); it != mExplosions.end (); it++) {
			if ((*it)->isDead ()) {
				delete *it;
				it = mExplosions.erase (it);
				it--;
			}
			else {
				(*it)->update ();
			}
		}
		
		if (mSpawnModifierCount == 0) {
		    mSpawnModifier = 1.0f;
		}
		else {
		    mSpawnModifierCount--;
		}
		
		mParticleSystemA->update ();
		mParticleSystemB->update ();
		mParticleSystemC->update ();
		mBackground->update ();
	}
	
	if (al_get_audio_stream_position_secs (mMusic->getStream ()) >= al_get_audio_stream_length_secs (mMusic->getStream ()) - 0.1) {
		music ();
	}
}

/***************************************************** Cycle **********************************************************/
void Game::cycle () {
	// Afin de s'assurer qu'on n'utilise pas le Renderer depuis cette fonction (multithreading...).
	Entity::setRenderer (NULL);

	if (mState == Game::STATE_PLAY || mState == Game::STATE_SCORE || mState == Game::STATE_GETNAME) {
		if (mPlayer != NULL) {
			mPlayer->cycle ();
		}
		
		// Collisions Player -> Ennemies
		for (auto it = mPlayerProjectiles.begin (); it != mPlayerProjectiles.end (); it++) {
			for (auto ite = mEnnemies.begin (); ite != mEnnemies.end (); ite++) {
				if ( (*it)->handleCollision (*ite) ) {
					(*ite)->addDamages ((*it)->getDamages ());
					(*it)->addDamages (100);
					if ((*it)->isMain() && mPlayer != NULL) {
					    mPlayer->incShootTouched();
					}
				}
			}
		}
		
		// Collisions Player -> Bonus
		if (mPlayer != NULL) {
			for (auto it = mBonus.begin (); it != mBonus.end (); it++) {
				if ((*it)->isCollide (mPlayer)) {
					(*it)->onTake ();
					if ((*it)->getSample () != NULL) {
					    (*it)->getSample ()->play (1.0f, 0.0f, 1.0f, false);
				    }
				}
			}
		}
		
		
		
		
		// Collisions Ennemies -> Player
		if (mPlayer != NULL) {
			for (auto it = mEnnemiesProjectiles.begin (); it != mEnnemiesProjectiles.end (); it++) {
			    if (mPlayer->getShield () > 0) {
			        if ((mPlayer->getPosition () - (*it)->getPosition () + lab::math::Vector<float>(24, 24)).length () < 48) {
			            mPlayer->addDamages ((*it)->getDamages ());
						(*it)->addDamages (10);
			        }
			    }
				else if ((*it)->handleCollision (mPlayer)) {
						mPlayer->addDamages ((*it)->getDamages ());
						(*it)->addDamages (10);
				}
			}
		}
		
		
		for (auto it = mEnnemies.begin (); it != mEnnemies.end (); it++) {
			(*it)->cycle ();
			if (mPlayer != NULL) {
				if ((*it)->handleCollision (mPlayer)) {
					(*it)->addDamages ((int) (*it)->getTakedInFace ().length ());
					mPlayer->addDamages ((int) mPlayer->getTakedInFace ().length ());
				}
			}
		}
	}
	
	/*std::cout << "Projectiles joueur : " << mPlayerProjectiles.size () << std::endl;
	std::cout << "Projectiles ennemis : " << mEnnemiesProjectiles.size () << std::endl;
	std::cout << "Ennemis : " << mEnnemies.size () << std::endl;*/

	// A partir de là c'est bon.
	Entity::setRenderer (mRenderer);
}

/***************************************************** Music **********************************************************/
void Game::music () {
	util::Value v = util::Value (rand () % 11);
	
	std::string name = "music" + v.getValue ();
	
	if (mMusic != NULL) {
		mMusic->rewind ();
		mMusic->stop ();
	}
	
	mMusic = mResources->getStream (name);
	mMusic->play (false);
	
	//std::cout << al_get_audio_stream_length_secs (mMusic->getStream ()) << std::endl;
}

/***************************************************** Render *********************************************************/
void Game::render () {
	mRenderer->render ();
}

/**************************************************** Shutdown ********************************************************/
void Game::shutdown () {
	stop ();
	
	mRenderer->removeDrawable (mBackground);
	delete mBackground;

	delete mPauseText;
	delete mQuitText;
	
	mRenderer->removeDrawable (mScoreText);
	delete mScoreText;

	delete mParticleSystemA;
	delete mParticleSystemB;
	delete mParticleSystemC;

	delete mRenderer;
	
	mMusic = NULL;
	
	mResources->unload ();
	delete mResources;

	Activity::shutdown ();
}

/****************************************************** Misc **********************************************************/
void Game::switchPause () {
	if (mState == Game::STATE_PAUSE) {
		mRenderer->removeDrawable (mPauseText);
		mState = Game::STATE_PLAY;
	}
	else if (mState == Game::STATE_PLAY) {
		mRenderer->addDrawable (mPauseText);
		mState = Game::STATE_PAUSE;
	}
}
		
void Game::switchExit () {
	static Bind *bexit, *bsexit;
	static int last_state;
	static std::list<Drawable*> last_drawables;

	if (mState == Game::STATE_PAUSE) {
		mRenderer->removeDrawable (mPauseText);
		last_drawables.push_front (mPauseText);
	}
	
	if (mState == Game::STATE_PLAY || mState == Game::STATE_PAUSE || mState == Game::STATE_SCORE || mState == Game::STATE_GETNAME) {
		mRenderer->addDrawable (mQuitText);
		last_state = mState;
		mState = Game::STATE_EXIT;
		// Add bind.
		bexit = new Bind ( new KeyEventChecker (ALLEGRO_KEY_Y), new ExitTask (), false );
		bsexit = new Bind ( new KeyEventChecker (ALLEGRO_KEY_N), new SwitchExitTask (), false );
		mBinder.addBind ("keyboard", "key_up", bexit);
		mBinder.addBind ("keyboard", "key_up", bsexit);
	}
	else {
		mRenderer->removeDrawable (mQuitText);
		mState = last_state;
		for (auto it = last_drawables.begin (); it != last_drawables.end (); it++) {
			mRenderer->addDrawable (*it);
			it = last_drawables.erase (it);
			it--;
		}
	}
}

void Game::exit () {
	if (mState == Game::STATE_EXIT) {
		getEngine ()->exit ();
	}
}

void Game::start () {
	// Données du jeu essentielles au binds.
	mPlayer = new Player (Vector<float> (480, 270), mResources, mParticleSystemA);
	
	mLifeBar = new LifeBar (Vector<float> (10, 20), &mPlayer, mResources);
	mRenderer->addDrawable (mLifeBar);
	mShieldBar = new ShieldBar (Vector<float> (10, 5), &mPlayer, mResources);
	mRenderer->addDrawable (mShieldBar);
	
	mIsWeaponBonus = false;
	
	mSpawnModifier = 1.0f;
	mSpawnModifierCount = 0;
	
	// Binds            Type     Subtype      	    Bind                EventChecker                            Task                                      Temporary
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_P), 	new SwitchPauseTask (&mState, mRenderer, mPauseText), 	false ) );
	mBinder.addBind ("video", 	 "switch_in",	new Bind ( new EverEventChecker (), 				new SwitchPauseTask (&mState, mRenderer, mPauseText), 	false ) );
	mBinder.addBind ("video", 	 "switch_out",	new Bind ( new EverEventChecker (), 				new SwitchPauseTask (&mState, mRenderer, mPauseText), 	false ) );
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_ESCAPE),new SwitchExitTask (), 									false ) );
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_F2),	new RestartTask (), 									false ) );
	
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_M), 	new SwitchMusicTask (this), 							false ) );
	
	mBinder.addBind ("keyboard", "key_down", 	new Bind ( new KeyEventChecker (ALLEGRO_KEY_LEFT), 	new PlayerMoveTask (&mPlayer, Vector<float> (-2.0f, 0.0f)), 		false ) );
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_LEFT), 	new PlayerMoveTask (&mPlayer, Vector<float> (2.0f, 0.0f)), 		false ) );
	
	mBinder.addBind ("keyboard", "key_down", 	new Bind ( new KeyEventChecker (ALLEGRO_KEY_RIGHT), new PlayerMoveTask (&mPlayer, Vector<float> (2.0f, 0.0f)), 		false ) );
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_RIGHT), new PlayerMoveTask (&mPlayer, Vector<float> (-2.0f, 0.0f)), 		false ) );
	
	mBinder.addBind ("keyboard", "key_down", 	new Bind ( new KeyEventChecker (ALLEGRO_KEY_UP), 	new PlayerMoveTask (&mPlayer, Vector<float> (0.0f, -2.0f)), 		false ) );
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_UP), 	new PlayerMoveTask (&mPlayer, Vector<float> (0.0f, 2.0f)), 		false ) );
	
	mBinder.addBind ("keyboard", "key_down", 	new Bind ( new KeyEventChecker (ALLEGRO_KEY_DOWN), 	new PlayerMoveTask (&mPlayer, Vector<float> (0.0f, 2.0f)), 		false ) );
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_DOWN), 	new PlayerMoveTask (&mPlayer, Vector<float> (0.0f, -2.0f)), 		false ) );
	
	mBinder.addBind ("keyboard", "key_down", 	new Bind ( new KeyEventChecker (ALLEGRO_KEY_SPACE), new PlayerShootTask (&mPlayer), 							false ) );
	mBinder.addBind ("keyboard", "key_up", 		new Bind ( new KeyEventChecker (ALLEGRO_KEY_SPACE), new PlayerShootTask (&mPlayer), 							false ) );
	
	// Ennemies
	ennemy::Ennemy::setPlayer (&mPlayer);
	
	// Bonus
	Bonus::setPlayer (mPlayer);
	
	mScoreV = 0;
	updateScore ();
}

void Game::stop () {
	mBinder.clearBinds ();
	
	mParticleSystemA->clearParticles ();
	mParticleSystemB->clearParticles ();
	mParticleSystemC->clearParticles ();
	
	for (auto it = mEnnemies.begin (); it != mEnnemies.end (); it++) {
		delete *it;
	}
	mEnnemies.clear ();
	
	for (auto it = mEnnemiesProjectiles.begin (); it != mEnnemiesProjectiles.end (); it++) {
		delete *it;
	}
	mEnnemiesProjectiles.clear ();
	
	for (auto it = mPlayerProjectiles.begin (); it != mPlayerProjectiles.end (); it++) {
		delete *it;
	}
	mPlayerProjectiles.clear ();
	
	for (auto it = mBonus.begin (); it != mBonus.end (); it++) {
		delete *it;
	}
	mBonus.clear ();
	
	for (auto it = mExplosions.begin (); it != mExplosions.end (); it++) {
		delete *it;
	}
	mExplosions.clear ();
	
	if (mLifeBar != NULL) {
		mRenderer->removeDrawable (mLifeBar);
		delete mLifeBar;
		mLifeBar = NULL;
	}
	
	if (mShieldBar != NULL) {
		mRenderer->removeDrawable (mShieldBar);
		delete mShieldBar;
		mShieldBar = NULL;
	}
	
	if (mPlayer != NULL) {
		delete mPlayer;
		mPlayer = NULL;
	}
	
	// Si scores
	if (mScore != NULL) {
		try {
			mRenderer->removeDrawable (mScore);
		} catch (const Exception& e) {
			
		}
		delete mScore;
		mScore = NULL;
	}
	
	// Si saisie du nom
	if (mNameSeizureText != NULL) {
		mRenderer->removeDrawable (mNameSeizureText);
		mRenderer->removeDrawable (mNameText);
		
		delete mNameSeizureText;
		delete mNameText;
		
		mNameSeizureText = NULL;
		mNameText = NULL;
	}
}

void Game::restart () {
	if (mState != Game::STATE_EXIT) {
		stop ();
		start ();
		mState = Game::STATE_PLAY;
	}
	
	mToRestart = false;
}

void Game::switchToScoreScreen () {
	// Destruction des binds
	mBinder.clearBinds ();
	mBinder.addBind ("keyboard", "key_up", new Bind ( new KeyEventChecker (ALLEGRO_KEY_ESCAPE), new SwitchExitTask (), false ) );
	
	// Ouverture des scores
	mScore = new Score (mResources->getFont ("font_normal"), mResources->getFont ("font_little"));
	mScore->load (getEngine ()->getUserConfigPath () + "score.bin");
	
	if (mScore->isIn (mScoreV)) {
		mState = STATE_GETNAME;
		
		mNameText = new Text (Vector<int> (480, 240), Vector<int> (), 0.0f, 102, mResources->getFont ("font_normal"), 
							  al_map_rgb (255, 255, 255), "Your name : ", Text::ALIGN_RIGHT);
		mRenderer->addDrawable (mNameText);
		
		mNameSeizureText = new Text (Vector<int> (480, 240), Vector<int> (), 0.0f, 102, mResources->getFont ("font_normal"), 
									 al_map_rgb (0, 255, 128), "", Text::ALIGN_LEFT);
		mRenderer->addDrawable (mNameSeizureText);
		
		mBinder.addBind ("keyboard", "key_char", new Bind ( new EverEventChecker (), 	new NameSeizureTask (), false ) );
		mBinder.addBind ("keyboard", "key_up", new Bind ( new KeyEventChecker (ALLEGRO_KEY_ENTER), 	new FinishNameSeizureTask (), false ) );
		
		mFinishNameSeizure = false;
	}
	else {	
		mRenderer->addDrawable (mScore);
	
		mState = STATE_SCORE;
		mBinder.addBind ("keyboard", "key_up", new Bind ( new KeyEventChecker (ALLEGRO_KEY_F2), 	new RestartTask (), false ) );
	}
}

void Game::finishNameSeizure () {
	mScore->add (mNameSeizureText->getText (), mScoreV);

	mScore->save (getEngine ()->getUserConfigPath () + "score.bin");

	mRenderer->removeDrawable (mNameSeizureText);
	mRenderer->removeDrawable (mNameText);
	
	delete mNameSeizureText;
	delete mNameText;
	
	mNameSeizureText = NULL;
	mNameText = NULL;
	
	mBinder.clearBinds ();
	mRenderer->addDrawable (mScore);
	mState = STATE_SCORE;
	mBinder.addBind ("keyboard", "key_up", new Bind ( new KeyEventChecker (ALLEGRO_KEY_F2), 	new RestartTask (), false ) );
	mBinder.addBind ("keyboard", "key_up", new Bind ( new KeyEventChecker (ALLEGRO_KEY_ESCAPE), new SwitchExitTask (), false ) );
	
	mFinishNameSeizure = false;
}

void Game::updateScore () {
	std::string str = "Score : ";
	util::Value val (mScoreV);
	
	str += val.getValue ();
	
	mScoreText->setText (str);
}

