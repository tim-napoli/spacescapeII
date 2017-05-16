#ifndef _lab_game_Entity_hpp_
#define _lab_game_Entity_hpp_

#include "lab/physic/Object.hpp"
#include "lab/graphic/Drawable.hpp"
#include "lab/graphic/Renderer.hpp"

namespace lab {
namespace game {

/*!
 * \brief An entity is an object that can link a Drawable to a physical object, destinated to join a world, and have
 * 		  interactions with other entities.
 */
class Entity : public physic::Object {
	protected:
		graphic::Drawable* mDrawable;
		static graphic::Renderer* renderer; // Only one renderer will be used for all entities ?

	public:
		Entity (int mass, 
			    const math::Vector<float>& position, 
			    const math::Vector<float>& speed,
			    const math::Box<float>& box);

		virtual ~Entity ();

		virtual graphic::Drawable* getDrawable () const {return mDrawable;}

		void syncronizeDrawable ();

		virtual void cycle () = 0;
		
		math::Vector<float> getDimensions () const {return mBox.getPosition () + mBox.getDimensions ();}
		
		/*!
		 * \brief Set the renderer of the entities.
		 */
		static void setRenderer (graphic::Renderer* r) {renderer = r;}
};

}}

#endif

