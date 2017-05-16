#ifndef _box_hpp_
#define _box_hpp_

#include "lab/math/Vector.hpp"

namespace lab {
namespace math {

/*!
 * \brief A box implemting a basic interface.
 */
template <typename T>
class Box {

	protected:
		Vector<T> mPosition, mDimensions;

	public:
		/*!
		 * \brief Default constructor.
		 */
		Box ();

		/*!
		 * \brief Coordinates based constructor.
		 */
		Box (T left, T top, T right, T bottom);

		/*!
		 * \brief Vector based constructor.
		 */
		Box (Vector<T> position, Vector<T> dimensions);

		/*!
		 * \brief Copy constructor.
		 */
		Box (const Box<T>& box);

		/*!
		 * \brief Destructor.
		 */
		virtual ~Box ();

		/*!
		 * \brief Get the box's position.
		 * \return the position's vector.
		 */
		inline Vector<T> getPosition () const {return mPosition;}

		/*!
		 * \brief Get the box's left value.
		 * \return the box's left value.
		 */
		inline T getLeft () const {return mPosition.x;}

		/*!
		 * \brief Get the box's right value.
		 * \return the box's right value.
		 */
		inline T getRight () const {return mPosition.x + mDimensions.x;}

		/*!
		 * \brief Get the box's top value.
		 * \return the box's top value.
		 */
		inline T getTop () const {return mPosition.y;}


		/*!
		 * \brief Get the box's bottom value.
		 * \return the box's bottom value.
		 */
		inline T getBottom () const {return mPosition.y + mDimensions.y;}

		/*!
		 * \brief Get the box's width.
		 * \return the box's width.
		 */
		inline T getWidth () const {return mDimensions.x;}

		/*!
		 * \brief Get the box's height.
		 * \return the box's height.
		 */
		inline T getHeight () const {return mDimensions.y;}

		/*!
		 * \brief Get the box's dimensions Vector.
		 * \return the box's dimensions.
		 */
		inline Vector<T> getDimensions () const {return mDimensions;}

		/*!
		 * \brief Looks if a point (as a Vector) is in the box.
		 * \param p The point to test.
		 * \return True if p is in the box.
		 */
		bool contains (const Vector<T>& p) const;

		/*!
		 * \brief Looks if a Box is intersecting this Box.
		 * \param box The box to test.
		 * \return True if p is in the box.
		 */
		bool intersects (const Box<T>& box) const;

		/*!
		 * \brief Get the translated box.
		 * \param v The translation's vector.
		 * \return The translated box.
		 */
		Box<T> getTranslated (const Vector<T>& v) const;

		/*!
		 * \brief Translate the box.
		 * \param v The translation's vector.
		 */
		void translate (const Vector<T>& v) const;
};

template <typename T>
Box<T>::Box () {
	this->mPosition = Vector<T> ();
	this->mDimensions = Vector<T> ();
}

template <typename T>
Box<T>::Box (T left, T top, T right, T bottom) {
	this->mPosition = Vector<T> (left, top);
	this->mDimensions = Vector<T> (right - left, bottom - top);
}

template <typename T>
Box<T>::Box (Vector<T> position, Vector<T> dimensions) {
	this->mPosition = Vector<T> (position);
	this->mDimensions = Vector<T> (dimensions);
}

template <typename T>
Box<T>::Box (const Box<T>& box) {
	this->mPosition = Vector<T> (box.getPosition ());
	this->mDimensions = Vector<T> (box.getDimensions ());
}

template <typename T>
Box<T>::~Box () {

}

template <typename T>
bool Box<T>::contains (const Vector<T>& p) const  {
	return !(p.x < this->getLeft () || p.x > this->getRight () || p.y < this->getTop () || p.y > this->getBottom ());
}

template <typename T>
bool Box<T>::intersects (const Box<T>& box) const {
	return !(box.getRight () < this->getLeft () || box.getLeft () > this->getRight () || box.getBottom () < this->getTop () || box.getTop () > this->getBottom ());
}

template <typename T>
Box<T> Box<T>::getTranslated (const Vector<T>& v) const {
	return Box<T> (this->getLeft () + v.x, this->getTop () + v.y, this->getRight () + v.x, this->getBottom () + v.y);
}

template <typename T>
void Box<T>::translate (const Vector<T>& v) const {
	this->mPosition += v;
}

}}

#endif

