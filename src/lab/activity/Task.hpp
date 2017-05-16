#ifndef _lab_activity_Task_hpp_
#define _lab_activity_Task_hpp_

namespace lab {
namespace activity {

/*!
 * \brief An Activity's Task is an object linked to an Activity and charged to make some things on it, in function of an
 *		  Event.
 *
 * An Activity Task is generaly used with a Binder. The Binder will receive an Event from a Device (or other generator),
 * and will execute a Task corresponding to the event (for exemple, a keyboard event informing that the 'A' key has been
 * pressed.
 */
class Task {
	public:
		/*!
		 * \brief Constructor.
		 */
		Task ();

		/*!
		 * \brief Destructor.
		 */
		virtual ~Task ();

		/*!
		 * \brief Instructions of the Task.
		 * \param event The Event that generated this execution.
		 */
		virtual void execute (const event::Event& event) const = 0;
};

}}

#endif

