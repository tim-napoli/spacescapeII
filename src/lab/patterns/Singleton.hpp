#ifndef _lab_pattern_Singleton_hpp_
#define _lab_pattern_Singleton_hpp_

namespace lab {
/*!
 * \brief The Singleston Pattern.
 */
namespace pattern {

template <class T>
class Singleton {
	public:
		static T& getInstance () {
			static T theInstance;
			return theInstance;
		}
};

}}

#endif

