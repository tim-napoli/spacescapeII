#ifndef _lab_io_Device_hpp_
#define _lab_io_Device_hpp_


#include <string>
#include "lab/event/Generator.hpp"

namespace lab {

class Exception;

/*!
 * \brief The input/output module. Derived objects are the intermediate between the user and the system.
 */
namespace io {

/*!
 * \brief A Device is a base object for all i/o objects of this space.
 *
 * The Device class is an abstract class destined to generate system event, and notifies them to the Engine.
 * A Device must be initialized (to allow it to generate event, hm ?), shutdowned (A begin, an end, it is the world),
 * and having the handleInput method duly implemented.
 * The name is not important for now.
 */
class Device : public event::Generator {
	
	protected:
		std::string 			mName;

	public:
		/*!
		 * \brief Device constructor.
		 */		
		Device (const std::string& name);

		/*!
		 * \brief Device destructor.
		 */
		virtual ~Device ();

		/*!
		 * \brief Get the name of the device.
		 * \return The device's name.
		 */
		const std::string& getName () const {return mName;}

		/*!
		 * \brief Initialize the device.
		 * \throw lab::Exception If the device cannot be initialized.
		 */
		virtual void initialize () throw (lab::Exception) = 0;

		/*!
		 * \brief Shutdown the device.
		 */
		virtual void shutdown () = 0;

		/*!
		 * \brief Handle the inputs events of this device (notify the listeners).
		 */
		virtual void handleInput () = 0;

		/*!
		 * \brief What will do the device in one loop.
		 */
		virtual void cycle () = 0;
};

}}

#endif

