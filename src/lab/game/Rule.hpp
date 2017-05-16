#ifndef _lab_game_Rule_hpp_
#define _lab_game_Rule_hpp_

#include <list>
#include "lab/game/BehavioredEntity.hpp"

namespace lab {
namespace game {

/*!
 * \brief A Rule is something that will say what kind of interactions can have entities together, and what effects have 
 * 		  theses interactions.
 *		  A rule is defined between two entity groups (by the list of theses groups).
 */
class Rule {
	private:
		std::list<BehavioredEntity*> *mGroupA, *mgroupB;
		
	public:
		/*!
		 * \brief Constructor.
		 * \param groupA The first group to connect...
		 * \param groupB ... with the second.
		 */
		Rule (std::list<BehavioredEntity*>* groupA, std::list<BehavioredEntity*>* groupB);
		
		/*!
		 * \brief Destructor.
		 */
		~Rule ();
		
		/*!
		 * \brief Check if the rule must be applicated.
		 */
		virtual bool check (BehavioredEntity* A, BehavioredEntity* B) = 0;
		
		/*!
		 * \brief Apply the rule.
		 */
		virtual void apply (BehavioredEntity* A, BehavioredEntity* B) = 0;
		
		/*!
		 * \brief Process this rule.
		 */
		void process ();
};

}}

#endif

