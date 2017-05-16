#ifndef _lab_util_Value_hpp_
#define _lab_util_Value_hpp_

#include <sstream>

namespace lab {
namespace util {

/*!
 * \brief A Value is an object which can convert value from different types to a string, and retrieve this string as
 * 		  value of different types.
 */
class Value {
	private:
		std::string mValue;

	public:
		/*!
		 * \brief Value constructor.
		 * \param value The value as a string.
		 */
		Value (const std::string& value);

		/*!
		 * \brief Value constructor.
		 * \param value The value as a specific type.
		 */
		template <typename T>
		inline Value (T value);

		/*!
		 * \brief Value destructor.
		 */
		~Value ();

		/*!
		 * \brief Get the value as a string.
		 * \return The value as a string.
		 */
		const std::string& getValue () const {return mValue;}

		/*!
		 * \brief Get the value as a specific type.
		 * \return The Value as a specific type.
		 */
		template <typename T>
		inline T getValue () const;

		/*!
		 * \brief Set the value as a string.
		 * \param value The value's string to set.
		 */
		void setValue (const std::string& value) {mValue = value;}

		/*!
		 * \brief Set the value as a specific type.
		 * \param value The value's type to set.
		 */
		template <typename T>
		inline void setValue (T value);	
};

template <typename T>
inline Value::Value (T value) {
	setValue (value);
}

template <typename T>
inline T Value::getValue () const {
	std::stringstream ss (mValue);
	T result;
	return ss >> result ? result : 0;
}

template <typename T>
inline void Value::setValue (T value) {
	std::stringstream ss;
	ss << value;
	mValue = ss.str ();
}

}}

#endif

