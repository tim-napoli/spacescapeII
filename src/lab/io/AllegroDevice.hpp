#ifndef _lab_io_AllegroDevice_hpp_
#define _lab_io_AllegroDevice_hpp_

#include <string>

#include <allegro5/allegro.h>
#include "lab/io/Device.hpp"

namespace lab {

namespace event {
	class Generator;
}

class Exception;

namespace io {

/*!
 * \brief A device using Allegro to work.
 *
 * This kind of Device is used as Allegro's wrapper.
 * It will register an Allegro event source to an Allegro event queue.
 */
class AllegroDevice : public Device {
	private:
		ALLEGRO_EVENT_QUEUE* mEvents;

	protected:
		void registerAllegroEventSource (ALLEGRO_EVENT_SOURCE* source);
		void unregisterAllegroEventSource (ALLEGRO_EVENT_SOURCE* source);
		bool getNextAllegroEvent (ALLEGRO_EVENT* e);

	public:
		AllegroDevice (const std::string& name);

		virtual ~AllegroDevice ();

		virtual void initialize () throw (lab::Exception);

		virtual void shutdown ();

		virtual void handleInput () = 0;

		virtual void cycle () = 0;
};

}}

#endif

