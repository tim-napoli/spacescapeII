#ifndef _lab_game_World_hpp_
#define _lab_game_World_hpp_

#include <list>
#include <boost/unordered_map.hpp>

#include "lab/Exception.hpp"
#include "lab/game/BehavioredEntity.hpp"

namespace lab {
namespace game {

/*!
 * \brief A world is an ensemble of game objects which works together. In classical terms, it corresponds to a game
 *		  level.
 *		  It will contains different lists of entities which can have interactions together, or not (like decorations).
 */
class World {
	private:
		boost::unordered_map<std::string, std::list<BehavioredEntity*>*> mEntityGroups;

	public:
		/*!
		 * \brief Constructor.
		 */
		World ();
		
		/*!
		 * \brief Destructor.
		 */
		virtual ~World ();
		
		/*!
		 * \brief Add a new entity group. Do nothing if the group already exists.
		 * \param group The group name.
		 */
		void addGroup ( const std::string& group ) {mEntityGroups.emplace ( group, new std::list<BehavioredEntity*> () );}
		
		/*!
		 * \brief Get a reference to a group.
		 * \param name The name of the group.
		 * \throw Exception if the group doesn't exist.
		 */
		std::list<BehavioredEntity*>* getGroup ( const std::string& group ) const throw (lab::Exception);
		
		/*!
		 * \brief Will update the world (creation of new objects + update of each object).
		 */
		void update ();	
		
		/*!
		 * \brief Will make all what the world is supposed to do each tick.
		 */
		void cycle ();		
};

}}

#endif

