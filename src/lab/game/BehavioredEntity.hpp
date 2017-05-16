#ifndef _lab_game_BehavioredEntity_hpp_
#define _lab_game_BehavioredEntity_hpp_

#include <cassert>

#include "lab/Exception.hpp"
#include "lab/game/Entity.hpp"
#include "lab/game/Behavior.hpp"

#include "lab/graphic/Renderer.hpp"

namespace lab {
namespace game {

class World;

/*!
 * \brief A behaviored entity is an entity which can have more than one behavior.
 *		  A behaviored entity ever  have a reference to a World (same world  for each entity), that permits the entity
 *		  to have feelings about that world, and admits it to choose its behavior in function of its environnement.
 *		  Behaviors are connected each together like states of an automaton with BehaviorLink.
 *		  Each Behavior is attached to a specific Drawable.
 */
class BehavioredEntity : public Entity {
	private:
		int mNBehaviors;
		Behavior* mCurrentBehavior;
		Behavior** mBehaviors;
	
		static World* world;	// No parallel worlds needed !
	
	public:
		/*!
		 * \brief Constructor.
		 * \param nbehaviors The number of differents behaviors this entity have.
		 */
		BehavioredEntity (int mass, 
			    		  const math::Vector<float>& position, 
			    		  const math::Vector<float>& speed,
			    		  const math::Box<float>& box,
			    		  int nbehaviors);
		
		/*!
		 * \brief Destructor.
		 */
		virtual ~BehavioredEntity ();
		
		/*!
		 * \brief Attach a new behavior.
		 */
		void setBehavior (int n, Behavior* behavior) {mBehaviors [n] = behavior;}
		
		/*!
		 * \brief Set the current behavior.
		 */
		void setCurrentBehavior (int behavior) {assert (behavior < mNBehaviors); mCurrentBehavior = mBehaviors [behavior];}
		
		/*!
		 * \brief Set the drawable of the indiced behavior.
		 */
		void setDrawable (int behavior);
		
		/*!
		 * \brief Get a behavior.
		 */
		Behavior* getBehavior (int n) {return mBehaviors [n];}
		
		/*!
		 * \brief The update method of this Entity.
		 */
		virtual void update ();
		
		/*!
		 * \brief Cycle this entity (will execute and switch behaviors).
		 * \throw Exception if there is no current behavior.
		 */
		virtual void cycle () throw (Exception);
		
		/*!
		 * \brief Set the world of the entities.
		 */
		static void setWorld (World* w) {world = w;}
};

}}

#endif

