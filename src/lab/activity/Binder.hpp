#ifndef _lab_activity_Binder_hpp_
#define _lab_activity_Binder_hpp_

#include <string>
#include <list>
#include <boost/unordered_map.hpp>

#include "lab/event/Event.hpp"
#include "lab/event/Listener.hpp"
#include "lab/activity/Task.hpp"

namespace lab {
namespace activity {

/*************************************************** EventChecker *****************************************************/
/*!
 * \brief An Event Checker is an object having a method to test if an Event corresponds to something of desirable.
 */
class EventChecker {
	public:
		virtual ~EventChecker ();
	
		/*!
		 * \brief Check if the passed event is corresponding to something of desirable.
		 * \param event The event.
		 */
		virtual bool check (const event::Event& event) const = 0;
};

/******************************************************* Bind *********************************************************/
class Bind {
	private:
		EventChecker* mChecker;
		Task* mTask;
		bool mTemporary;

	public:
		/*!
		 * \brief Constructor.
		 * \param checker The address of an EventChecker associated with this Bind.
		 * \param task The adress of a Task associated with this Bind.
		 * \param temporary If true, then the bind will be destroyed after one use.
		 */
		Bind (EventChecker* checker, Task* task, bool temporary);

		/*!
		 * \brief Destructor (will delete both task and checker).
		 */
		~Bind ();

		/*!
		 * \brief Execute the Task linked to this Bind.
		 * \param event The Event to relay to the Task.
		 */
		void execute (const event::Event& event);

		/*!
		 * \brief Check if the Event will actionnate the Bind.
		 * \param event The event to check.
		 */
		bool check (const event::Event& event);
		
		/*!
		 * \brief Say if this bind must be destroyed after one use.
		 */
		bool isTemporary () const {return mTemporary;} 		 
};

/****************************************************** Binder ********************************************************/
class Binder : event::Listener {
	private:
		boost::unordered_map<std::string, boost::unordered_map<std::string, std::list<Bind*>>> mEventMap;

	public:
		/*!
		 * \brief Constructor.
		 */
		Binder ();

		/*!
		 * \brief Destructor.
		 */
		~Binder ();

		/*!
		 * \brief Add a Bind to the Binder.
		 * \param event_type The event type of the Bind (exemple : "keyboard").
		 * \param event_subtype The event subType of the Bind (exemple : "up").
		 * \param bind The Bind to add (will be destroyed at the Binder destruction).
		 */
		void addBind (const std::string& event_type, const std::string& event_subtype, Bind* bind);

		/*!
		 * \brief Remove all binds in the Binder.
		 */
		void clearBinds ();
		
		/*!
		 * \brief Remove all temporaries Binds.
		 */
		void clearTemporaries ();
		
		/*!
		 * \brief Remove bind with specified address.
		 */
		void clearBind (Bind* addr);

		/*!
		 * \brief The notify method of this Binder.
		 */
		void notify (const event::Event& event);
};

/*************************************************** EventCheckers ****************************************************/
/*!
 * \brief Event Checker for "keyboard.down" or "keyboard.up" events.
 */
class KeyEventChecker : public EventChecker {
	private:
		int mKeycode;

	public:
		KeyEventChecker (int keycode);

		~KeyEventChecker ();

		bool check (const event::Event& event) const;
};

class EverEventChecker : public EventChecker {
	public:
		EverEventChecker ();

		~EverEventChecker ();

		bool check (const event::Event& event) const;
};

}}

#endif

