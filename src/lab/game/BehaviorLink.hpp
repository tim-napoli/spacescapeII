#ifndef _lab_game_BehaviorLink_hpp_
#define _lab_game_BehaviorLink_hpp_

namespace lab {
namespace game {

class Behavior;

/*!
 * \brief A beahvior link is a class containing a test function that will return true when an entity with a certain
 *		  behavior should switch to another behavior.
 *		  The target behavior should not be created when calling the constructor of this object.
 */
class BehaviorLink {
	int mBehavior;
	
	public:
	
		/*!
		 * \brief Constructor.
		 * \param The behavior which will be set if the link's conditions are ok.
		 */
		BehaviorLink (int behavior);
		
		/*!
		 * \brief Destructor.
		 */
		virtual ~BehaviorLink ();
		
		/*!
		 * \brief Get the behavior linked to this BehaviorLink.
		 */
		int getBehavior () const {return mBehavior;}
	
		/*!
		 * \brief This function must return true if the linked behavior should be set.
		 * \return true if the linked behavior should be set.
		 */
		virtual bool check () = 0;
};

}}

#endif

