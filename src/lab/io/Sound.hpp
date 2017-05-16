#ifndef _lab_io_Sound_hpp_
#define _lab_io_Sound_hpp_

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "lab/io/Device.hpp"
#include "lab/config/Configurable.hpp"

namespace lab {
namespace io {

/*!
 * \brief The Sound class is a configurable Device that will allow the user to use sounds.
 */
class Sound : public Device, public config::Configurable {
	private:
		ALLEGRO_MIXER* mMixer;
		ALLEGRO_VOICE* mVoice;
	public:
		/*!
		 * \brief Constructor.
		 */
		Sound ();
		
		/*!
		 * \brief Destructor.
		 */
		~Sound ();
		
		/*!
		 * \brief Initialize the sound device.
		 * \throw lab::Exception on error.
		 */
		void initialize () throw (lab::Exception);
		 
		 /*!
		  * \brief Shutdown the soud device.
		  */
		void shutdown ();
		 
		 /*!
		  * \brief Will transmits audio events to the engine (no effects for now).
		  */
		void handleInput ();
		 
		 /*!
		  * \brief A soud device cycle.
		  */
		void cycle ();
		
};

}}

#endif

