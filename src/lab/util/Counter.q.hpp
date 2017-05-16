#ifndef _lab_util_Counter_hpp_
#define _lab_util_Counter_hpp_

namespace lab {
namespace util {

/*!
 * \brief A counter is an object which exists to count.
 */
template <typename T>
class Counter {
	private:
		T mCount, mStart, mStop;
	
	public:
		/*!
		 * \brief Constructor.
		 * \param start The counter start value.
		 * \param stop The counter stop value (when the counter atteigns this value, it will return to start).
		 */
		Counter (T start, T stop);

		/*!
		 * \brief Destructor.
		 */
		~Counter ();

		
};

}}

#endif

