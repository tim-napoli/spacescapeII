#ifndef _lab_io_Keyboard_hpp_
#define _lab_io_Keyboard_hpp_

#include "lab/Exception.hpp"
#include "lab/io/AllegroDevice.hpp"

namespace lab {
namespace io {

class Keyboard : public AllegroDevice {

	public:

		/*!
		 * \brief Keyboard constructor.
		 */
		Keyboard ();

		/*!
		 * \brief Keyboard destructor.
		 */
		~Keyboard ();

		/*!
		 * \brief Initialize the Keyboard device.
		 */
		void initialize () throw (lab::Exception);

		/*!
		 * \brief Shutdown the Keyboard device.
		 */
		void shutdown ();

		/*!
		 * \brief This function will transmits events from the Keyboard to its listeners.
		 */
		void handleInput ();

		/*!
		 * \brief A Keyboard's Device cycle.
		 */
		void cycle ();
};

}}

#endif

