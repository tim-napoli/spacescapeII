#ifndef _lab_io_Video_hpp_
#define _lab_io_Video_hpp_

#include <string>
#include "lab/Exception.hpp"
#include "lab/config/Configurable.hpp"
#include "lab/io/AllegroDevice.hpp"

namespace lab {

namespace io {

/*!
 * \brief The video device. It wraps an ALLEGRO_DISPLAY and provides a more adapted interface.
 */
class Video : public AllegroDevice, public config::Configurable {
	private:
		// Configuration values
		std::string mWindowName;

		// Display (from Allegro)
		ALLEGRO_DISPLAY* mDisplay;

	public:
		
		/*!
		 * \brief Video device's constructor (direct configuration).
		 * \param window_name The name of the window.
		 */
		Video (const std::string& window_name);

		/*!
		 * \brief Video device's destructor
		 */
		~Video ();

		/*!
		 * \brief Initialize the Video device.
		 * \throw lab::Exception if an error is encountered.
		 */
		void initialize () throw (lab::Exception);

		/*!
		 * \brief Shutdown the Video device.
		 */
		void shutdown ();

		/*!
		 * \brief This function will transmits events from the Video to its listeners.
		 */
		void handleInput ();

		/*!
		 * \brief A Video's Device cycle.
		 */
		void cycle ();

		/*!
		 * \brief Get the display width.
		 */
		int getWidth () const {return al_get_display_width (mDisplay);}

		/*!
		 * \brief Get the display height.
		 */
		int getHeight () const {return al_get_display_height (mDisplay);}
		
		/*!
		 * \brief Get the display.
		 */
		ALLEGRO_DISPLAY* getDisplay () const {return mDisplay;}

		/*!
		 * \brief Resize the display.
		 * \param width The new width.
		 * \param height The new height.
		 */
		void resize (int width, int height);
};

}}

#endif

