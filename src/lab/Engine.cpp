#include <iostream>
#include <ctime>

#include "Engine.hpp"
#include "activity/Activity.hpp"
#include "Resources.hpp"

namespace lab {

Engine::Engine (const std::string& name, int fps) {
	mName = name;
	mExit = false;
	mShouldRedraw = false;
	mOtherThreadLaunched = false;

	mVideo = new io::Video (name);
	mKeyboard = new io::Keyboard ();
	mMouse = new io::Mouse ();
	mSound = new io::Sound ();

	mCurrentActivity = NULL;
	mActivities = boost::unordered_map<std::string, activity::Activity*> ();

	mFps = fps;
}

Engine::~Engine () {
	// Destruction des activités.
	for (auto it = mActivities.begin (); it != mActivities.end (); it++) {
		delete it->second;
	}
	mActivities.clear ();

	delete mVideo;
	delete mKeyboard;
	delete mMouse;
	delete mSound;
}

void Engine::initialize () throw (lab::Exception) {
	al_init ();
	al_init_primitives_addon ();
	al_init_image_addon ();
	al_init_font_addon ();
	al_init_ttf_addon ();

	srand (time (NULL));

	// Remplacement du nom de l'éxecutable.
	al_set_app_name (mName.c_str ());

	// Vérification de l'existence du dossier de configuration du moteur.
	if (!al_make_directory (Engine::getUserConfigPath ().c_str ())) {
		std::cout << "Engine::initialize warning : The configuration's directoty " << getUserConfigPath () << 
					 " is not exist and cannot be created." << std::endl;
	}

	// Chargement du fichier de configuration.
	config::Configuration config = config::Configuration ();
	std::string cfg_path = Engine::getUserConfigPath () + "labengine.cfg";
	try {
		config.load (cfg_path);
	} catch (const lab::Exception& exception) {
		std::cout << "Engine::initialize warning :\n\t" << exception.what () << std::endl;
		config::Configuration config = config::Configuration ();
	}
	mVideo->setConfiguration (config.extract ("video"));
	mSound->setConfiguration (config.extract ("Audio"));

	mVideo->initialize ();
	mVideo->registerListener (this);
	mKeyboard->initialize ();
	mKeyboard->registerListener (this);
	mMouse->initialize ();
	mMouse->registerListener (this);
	try {
		mSound->initialize ();
		mSound->registerListener (this);
	} catch (const lab::Exception& exception) {
		std::cout << "Engine::initialize warning : Cannot install sound device :\n\t" << exception.getMessage () << std::endl;
	}

	// Initialisation de l'activité courante.
	if (mCurrentActivity == NULL) {
		throw lab::Exception (0, "Engine::initialize error : No activity is setting to run (see Engine::addActivity).");
	}

	try {
		mCurrentActivity->initialize ();
		mVideo->registerListener (mCurrentActivity);
		mKeyboard->registerListener (mCurrentActivity);
		mMouse->registerListener (mCurrentActivity);
	} catch (const lab::Exception& e) {
		throw lab::Exception (1, "Engine::initialize error : Cannot start activity :\n\t" + e.getMessage ());
	}
}

void Engine::shutdown () {
	// Fermeture des activités.
	for (auto it = mActivities.begin (); it != mActivities.end (); it++) {
		if (it->second->isInitialized ()) {
			it->second->shutdown ();
		}
	}

	// Sauvegarde du fichier de configuration.
	config::Configuration config = mVideo->getConfiguration ();
	config.merge (mSound->getConfiguration ());
	std::string cfg_path = Engine::getUserConfigPath () + "labengine.cfg";
	try {
		config.save (cfg_path);
	} catch (const lab::Exception& exception) {
		std::cout << "Engine::shutdown warning :\n\t" << exception.what () << std::endl;
	}

	mKeyboard->shutdown ();
	mMouse->shutdown ();
	mVideo->shutdown ();
	mSound->shutdown ();

	al_uninstall_system ();
}

/**************************************************** Activities ******************************************************/
void Engine::addActivity (const std::string& name, activity::Activity* activity) throw (lab::Exception) {
	auto got = mActivities.find (name);
	if (got != mActivities.end ()) {
		throw lab::Exception (0, "Engine::addActivity : Activity \"" + name + "\" already exist.");
	}

	mActivities.emplace (name, activity);
	if (mCurrentActivity == NULL) {
		mCurrentActivity = activity;
	}
}

void Engine::startActivity (const std::string& name) throw (lab::Exception) {
	auto got = mActivities.find (name);
	if (got == mActivities.end ()) {
		throw lab::Exception (0, "Engine::startActivity : Activity \"" + name + "\" does not exist.");
	}

	if (mCurrentActivity != NULL) {
		mVideo->unregisterListener (mCurrentActivity);
		mKeyboard->unregisterListener (mCurrentActivity);
	}

	mCurrentActivity = got->second;
	if (!mCurrentActivity->isInitialized ()) {
		try {
			mCurrentActivity->initialize ();

			mVideo->registerListener (mCurrentActivity);
			mKeyboard->registerListener (mCurrentActivity);
		} catch (const lab::Exception& e) {
			throw lab::Exception (1, "Engine::startActivity : Activity \"" + name + "\" initialize failure :\n\t" + e.getMessage ());
		}
	}
}

/**************************************************** Controller ******************************************************/
void Engine::handleVideoEvent (const event::Event& event) {
	if (event.getSubType ().compare ("close") == 0) {
		mExit = true;
	}
	else if (event.getSubType ().compare ("resize") == 0) {
		mVideo->resize (event.getParameter ("width").getValue<int> (), 
						event.getParameter ("height").getValue<int> ()
					   );
		if (mCurrentActivity->getRenderer () != NULL) {
			mCurrentActivity->getRenderer ()->updateInfos ();
		}
	}
}

void Engine::handleKeyboardEvent (const event::Event& event) {
	(void) event;
}

void Engine::handleMouseEvent (const event::Event& event) {
	(void) event;
}

void Engine::notify (const event::Event& event) {
	if (event.getType ().compare ("video") == 0) {
		handleVideoEvent (event);
	} 
	else if (event.getType ().compare ("keyboard") == 0) {
		handleKeyboardEvent (event);
	}
}

/******************************************************* Loop *********************************************************/
static int fps = 0;

/*
static void* other_thread (ALLEGRO_THREAD* thread, Engine* engine) {
	(void) thread;

	engine->otherThreadLaunched ();
	al_init_user_event_source (&sync_event_source);
	sync_threads_queue = al_create_event_queue ();
	al_register_event_source (sync_threads_queue, &sync_event_source);

	while (!engine->isExiting ()) {
		// Attends un évenement du moteur.
		ALLEGRO_EVENT event;
		al_wait_for_event (sync_threads_queue, &event);
		if (event.user.type == ALLEGRO_GET_EVENT_TYPE ('D','R','A','W')) {
			//al_convert_bitmaps ();
			al_set_target_backbuffer (engine->getVideo ()->getDisplay ());		
		
			engine->getCurrentActivity ()->render ();
			
			engine->getVideo ()->cycle ();
			
			al_set_target_backbuffer (NULL);
			fps++;
			
			ALLEGRO_EVENT ret_event;
			ret_event.user.type = ALLEGRO_GET_EVENT_TYPE ('E','N','D','D');
			al_emit_user_event (&sync_event_source, &ret_event, NULL);
		}
		else {
			al_emit_user_event (&sync_event_source, &event, NULL);
		}
		
		std::cout << "ici !" << std::endl;
	}
	
	engine->otherThreadStopped ();

	return NULL;
}*/

static void* other_thread (ALLEGRO_THREAD* thread, Engine* engine) {
	static bool randomized = false;
	(void) thread;

	if (!randomized) {
		srand ((uint64_t) al_get_time ());
		randomized = true;
	}
	engine->getCurrentActivity ()->cycle ();

	return NULL;
}

void Engine::loop () {
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* timer_queue;

	// Installation du timer
	timer = al_create_timer (1.0 / mFps);
	timer_queue = al_create_event_queue ();
	al_register_event_source (timer_queue, al_get_timer_event_source (timer));

	al_start_timer (timer);
	
	ALLEGRO_THREAD* thread;
	

	double last_time = al_get_time (); // Pour compter les FPS.
	while (!mExit) {
		ALLEGRO_EVENT e;
		al_wait_for_event (timer_queue, &e);
		al_flush_event_queue (timer_queue);

		// Mise à jour des évenements d'entrée.
		mVideo->handleInput ();
		mKeyboard->handleInput ();

		// Joue l'activité.
		
		
		// Mise à jour de l'activité
		mCurrentActivity->update ();
		
		// Créé et lance le thread de cycle (ABANDON PROBL7ME D'ALEATOIRE SUR AUTRE THREAD !!!!!).
		//thread = al_create_thread (((void* (*) (ALLEGRO_THREAD*, void*)) other_thread), (void*) this);
		//al_start_thread (thread);
		
		// Rendu
		mCurrentActivity->cycle ();
		mCurrentActivity->render ();
		mVideo->cycle ();
		fps++;

		// Attente de l'autre thread.
		//al_join_thread (thread, NULL);
		//al_destroy_thread (thread);
		
		//al_set_target_backbuffer (getVideo ()->getDisplay ());
		//al_set_target_backbuffer (NULL);
		if (al_get_time () - last_time >= 1.0) {
			std::cout << "Fps (" << al_get_time () - last_time << ") : " << fps << std::endl;
			last_time = al_get_time ();
			fps = 0;
		} 
	}

	al_set_target_backbuffer (getVideo ()->getDisplay ());	

	al_stop_timer (timer);
	al_unregister_event_source (timer_queue, al_get_timer_event_source (timer));
	al_destroy_event_queue (timer_queue);
	al_destroy_timer (timer);
}

}

