#ifndef _lab_event_Generator_hpp_
#define _lab_event_Generator_hpp_

#include <list>

#include "lab/Exception.hpp"
#include "lab/event/Listener.hpp"
#include "lab/event/Event.hpp"

namespace lab {

namespace event {

class Generator {
	private:
		std::list<Listener*> mListeners;

	public:
		
		/*!
		 * \brief Constructor.
		 */
		Generator ();

		/*!
		 * \brief Destructor.
		 */
		virtual ~Generator ();

		/*!
		 * \brief Look if the specifidef listener is already registred.
		 * \param listener The address of the Listener.
		 * \return True if indeed the listener is already registred.
		 */
		bool isListenerRegistred (const Listener* listener) const;

		/*!
		 * \brief Register a new Listener to notify through this generator.
		 * \param listener The address of the Listener.
		 * \throw lab::Exception If this listener is already registred.
		 */
		void registerListener (Listener* listener) throw (lab::Exception);

		/*!
		 * \brief Unregister a listener from this generator.
		 * \param listener The address of the Listener to remove.
		 * \throw lab::Exception If the specified Listener does not exist.
		 */
		void unregisterListener (Listener* listener) throw (lab::Exception);
		
		/*!
		 * \brief Notify all the listeners with the specified event.
		 */
		void notifyAll (const Event& event);
};

}}

#endif

