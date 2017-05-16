#ifndef _lab_physic_Object_hpp_
#define _lab_physic_Object_hpp_

#include "lab/math/Vector.hpp"
#include "lab/math/Box.hpp"

namespace lab {
namespace physic {

/*!
 * \brief A physic::Object is a really simple object handling physic informations in a 2d world.
 *
 * 
 */
class Object {
	protected:
		int mMass;
		math::Vector<float> mPosition, mSpeed, mTakedInFace;
		math::Box<float> mBox;
		

	public:

		/*!
		 * \brief Constructor.
		 */
		Object (int mass = 1, 
				const math::Vector<float>& position = math::Vector<float> (), 
				const math::Vector<float>& speed = math::Vector<float> (),
				const math::Box<float>& box = math::Box<float> ());

		/*!
		 * \brief Destructor.
		 */
		virtual ~Object ();

		/*!
		 * \brief Get the object mass.
		 * \return The object mass.
		 */
		inline int getMass () const {return mMass;}

		/*!
		 * \brief Get the object position.
		 * \return The Object position.
		 */
		inline const math::Vector<float>& getPosition () const {return mPosition;}

		/*!
		 * \brief Get the object speed.
		 * \return The object speed.
		 */
		inline const math::Vector<float>& getSpeed () const {return mSpeed;}
		
		/*!
		 * \brief Get the "Taked in face" vector.
		 * \return The "Taked in face" vector.
		 */
		inline const math::Vector<float>& getTakedInFace () const {return mTakedInFace;}

		/*!
		 * \brief Get the collide box of the object (with an absolute position, not relative !).
		 * \return The box.
		 */
		inline math::Box<float> getBox () const {return mBox.getTranslated (mPosition);}

		/*!
		 * \brief Set the object's mass.
		 * \param mass The new object's mass.
		 */
		inline void setMass (int mass) {mMass = mass;}

		/*!
		 * \brief Set the object's position.
		 * \param position The new object's position.
		 */
		inline void setPosition (const math::Vector<float>& position) {mPosition = position;}

		/*!
		 * \brief Set the object's speed.
		 * \param speed The new object's speed.
		 */
		inline void setSpeed (const math::Vector<float>& speed) {mSpeed = speed;}

		/*!
		 * \brief Set the object's box. It should be relative to the object's position.
		 * \param box The new box.
		 */
		inline void setBox (const math::Box<float> box) {mBox = box;}

		/*!
		 * \brief Get the cinetic force of the object.
		 *
		 * This force is speed * mass.
		 */
		inline math::Vector<float> getCineticForce () const {return mSpeed * mMass;}

		/*!
		 * \brief Apply a force on the object (resulting in speed change at the end of the loop (in normal way)).
		 * \param f The force.
		 */
		void apply (const math::Vector<float>& f);

		/*!
		 * \brief Update the object position and speed.
		 */
		virtual void update ();

		/*!
		 * \brief Test if there is a collision between two objects.
		 * \param object The other object.
		 * \return True if the two objects collided.
		 */
		bool isCollide (const Object* object);

		/*!
		 * \brief Handle a Collision between two objects (will modify the speed of both objects).
		 */
		bool handleCollision (Object* object);
};

}}

#endif

