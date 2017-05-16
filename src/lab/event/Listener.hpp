#ifndef _lab_event_Listener_hpp_
#define _lab_event_Listener_hpp_

#include <list>

#include "lab/event/Event.hpp"

namespace lab {
namespace event {

/*!
 * \brief A Listener will receive events from Generators that register it.
 */
class Listener {
	public:
		/*!
		 * \brief This function will be called when an event::Generator generates an event and notify this Listener.
		 * \param event The generated event.
		 */
		virtual void notify (const Event& event) = 0;
};

}}

#endif

