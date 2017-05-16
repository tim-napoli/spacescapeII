#ifndef _lab_Exception_hpp_
#define _lab_Exception_hpp_

#include <string>
#include <exception>

namespace lab {

/*!
 * \brief A basic lab exception.
 */
class Exception : public std::exception {

	private:
		std::string mMessage;
		int 		mCode;

	public:
		Exception (int code, const std::string& message) throw ();

		virtual ~Exception () throw ();

		virtual const char* what () const throw ();

		/*!
		 * \brief Get the exception code.
		 * \return The exception code.
		 */
		int getCode () const {return mCode;}

		/*!
		 * \brief Get the message.
		 * \return The message.
		 */
		std::string getMessage () const {return mMessage;}
};

}

#endif

