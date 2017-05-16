#ifndef _lab_game_Behavior_hpp_
#define _lab_game_Behavior_hpp_

#include <vector>

#include "lab/graphic/Drawable.hpp"
#include "lab/game/BehaviorLink.hpp"

namespace lab {
namespace game {

class BehavioredEntity;

/*!
 * \brief An entity behavior is the actions an entity will have in a particular situation.
 *		  See BehavioredEntity for more details.
 */
class Behavior {
	protected:
		graphic::Drawable*		 	  mDrawable;
		std::vector<BehaviorLink*> 	  mLinks;

	public:
	
		/*!
		 * \brief Constructor.
		 * \param drwable The drawable of the entity with this behavior.
		 * \param nlinks The number of links to other behaviors this behavior have.
		 */
		Behavior (graphic::Drawable* drawable, int nlinks);
	
		/*!
		 * \brief Destructor. Will destroy the drawable.
		 */
		virtual ~Behavior ();
	
		/*!
		 * \brief Set a behavior link.
		 */
		void setLink (int n, BehaviorLink* link) {mLinks [n] = link;}
		
		/*!
		 * \brief Return the links.
		 */
		std::vector<BehaviorLink*>& getLinks () {return mLinks;}
		
		/*!
		 * \brief Return a link.
		 */
		BehaviorLink* getLink (int n) {return mLinks [n];}
		
		/*!
		 * \brief Get the drawable attached to this behavior.
		 * \return The drawable.
		 */
		graphic::Drawable* getDrawable () const {return mDrawable;}
	
		/*!
		 * \brief This method will be launched when the behavior just go to be.
		 */
		virtual void onSet () = 0;
		
		/*!
		 * \brief This method will be used each turn the behavior is used by its entity.
		 */
		virtual void cycle () = 0;
		
		/*!
		 * \brief This method will be launched when the behavior just go to be removed.
		 */
		virtual void onUnset () = 0;
};


}}

#endif

