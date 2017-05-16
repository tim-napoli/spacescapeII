#ifndef _lab_Engine_hpp_
#define _lab_Engine_hpp_

#include <list>
#include <string>
#include <boost/unordered_map.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "lab/Exception.hpp"
#include "lab/Resources.hpp"
#include "lab/config/Configuration.hpp"
#include "lab/event/Event.hpp"
#include "lab/event/Listener.hpp"
#include "lab/io/Video.hpp"
#include "lab/io/Keyboard.hpp"
#include "lab/io/Mouse.hpp"
#include "lab/io/Sound.hpp"

/*!
 * \brief The labengine main namespace.
 */
namespace lab {

namespace activity {
	class Activity;
}

/*!
 * \brief The main labengine class. Will make the link between the hardware (with Allegro) and the user activities.
 *
 * The lab::Engine class is the main class of the library. It will make the link between the Activity Graph and the 
 * inputs and outputs. 
 *
 */
class Engine : public event::Listener {

	private:
		std::string mName;
		bool		mExit;
		bool		mShouldRedraw, mDrawing, mOtherThreadLaunched;
		
		io::Video* 		mVideo;
		io::Keyboard*	mKeyboard;
		io::Mouse*		mMouse;
		io::Sound*		mSound;

		activity::Activity* mCurrentActivity;
		boost::unordered_map<std::string, activity::Activity*> mActivities;

		int mFps;
		bool mHaveSound;

	public:
		/*!
		 * \brief Constructor.
		 * \param name The name of the game.
		 * \param configuration The configuration to use.
		 * \param fps The number of frame per second of the engine.
		 */
		Engine (const std::string& name, int fps);

		/*!
		 * \brief Destructor.
		 */
		~Engine ();

		/*!
		 * \brief Initialize the engine. 
		 */
		void initialize () throw (lab::Exception);

		/*!
		 * \brief Shutdown the engine.
		 */
		void shutdown ();

		/*!
		 * \brief The engine loop.
		 */
		void loop ();

		/*!
		 * \brief Instructions to handle a Video Event.
		 * \param event The video event.
		 */
		void handleVideoEvent (const event::Event& event);

		/*!
		 * \brief Instructions to handle a Keyboard Event.
		 * \param event The keyboard event.
		 */
		void handleKeyboardEvent (const event::Event& event);
		
		/*!
		 * \brief Instructions to handle a Mouse Event.
		 * \param event The mouse event.
		 */
		void handleMouseEvent (const event::Event& event);

		/*!
		 * \brief The Engine notify function.
		 */
		void notify (const event::Event& event);

		/*!
		 * \brief Add an Activity to the Activity list. The first Activity added using this method will be the first to
		 *		  be started by the engine.
		 * \param name The Activity's name.
		 * \param activity The Activity's address.
		 * \throw lab::Exception If the Activity already exist.
		 */
		void addActivity (const std::string& name, activity::Activity* activity) throw (lab::Exception);

		/*!
		 * \brief Start an activity.
		 * \param name The Activity's name.
		 * \throw lab::Exception If this Activity does not exist (code = 0), or if the Activity cannot be initialized
		 *						 (code = 1).
		 */
		void startActivity (const std::string& name) throw (lab::Exception);
		
		/*!
		 * \brief Get the current activity which is running.
		 */
		activity::Activity* getCurrentActivity () const {return mCurrentActivity;}

		/*!
		 * \brief Set the engine to exit.
		 */
		void exit () {mExit = true;}
		
		/*!
		 * \brief Say if the engine must exit.
		 */
		bool isExiting () {return mExit;}

		/*!
		 * \return The adress of the Video Module.
		 */
		io::Video* getVideo () const {return mVideo;}
		
		/*!
		 * \brief Should the engine redraw ?
		 */
		bool shouldRedraw () const {return mShouldRedraw;}
		
		/*!
		 * \brief Set the engine to redraw.
		 */
		void setShouldRedraw (bool r) {mShouldRedraw = r;}
		
		/*!
		 * \brief State the other thread to launched ?
		 */
		void otherThreadLaunched () {mOtherThreadLaunched = true;}
		
		/*!
		 * \brief Set the other thread stopped.
		 */
		void otherThreadStopped () {mOtherThreadLaunched = false;}
		
		/*!
		 * \brief Set the engine drawing.
		 */
		void setDrawing (bool b) {mDrawing = b;}
		
		/*!
		 * \brief Say if the engine is drawing.
		 */
		bool isDrawing () {return mDrawing;}
		
		/*!
		 * \brief Get the wait time.
		 */
		double getWaitTime () const {return 0.001;}
		
		
		
		/*!
		 * \brief Say if the Engine can load and play sounds.
		 */
		

		/*!
		 * \brief Get the data configuration directory path.
		 * \return The path where to stock confiuration files.
		 */
		static std::string getUserConfigPath () { 
			return std::string ( al_path_cstr (al_get_standard_path (ALLEGRO_USER_SETTINGS_PATH), '/') );
		}

		/*!
		 * \brief Get the resources directory path.
		 * \return The path where to stock resource files.
		 */
		static std::string getResourcesPath () { 
			return std::string ( al_path_cstr (al_get_standard_path (ALLEGRO_RESOURCES_PATH), '/') );
		}
		
		/*!
		 * \brief Get the user data directory path.
		 * \return The path where to stock data files.
		 */
		static std::string getDataPath () { 
			return std::string ( al_path_cstr (al_get_standard_path (ALLEGRO_USER_DATA_PATH), '/') );
		}
};

}

#endif

