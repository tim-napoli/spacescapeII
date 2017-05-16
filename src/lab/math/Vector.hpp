#ifndef _vector_hpp_
#define _vector_hpp_

#include <cmath>

namespace lab {
namespace math {

/*!
 * \brief A 2d vector.
 *
 * The vector class provides useful methods for vector manipulations.
 */
template <typename T>
class Vector {
	public:
		T x, y;	/*! Position of the vector */

		/*!
		 * \brief Basic constructor.
		 * \param x The x-coordinate of the vector.
		 * \param y The y-coordinate of the vector.
		 *
		 * Basic constructor for the Vector class.
		 */
		Vector (T x = 0, T y = 0);

		/*!
		 * \brief Copy constructor.
		 * \param v The vector to copy.
		 */
		Vector (const Vector<T>& v);

		/*!
		 * \brief Destructor.
		 */
		virtual ~Vector ();

		/*!
		 * \brief Get the vector length.
		 * \return The length of the vector.
		 */
		float length () const;
		
		/*!
		 * \brief Get the angle of the vector.
		 * \param center The center from which calculate the angle.
		 * \return The angle in radiants.
		 */
		float angle (const Vector<T>& center = Vector<T> ()) const;

		/*!
		 * \brief Get the radiant angle between two vectors.
		 * \param center The center from which calculate the angle.
		 * \param v The other vector.
		 * \return The angle in radiants.
		 */
		float angleBetween (const Vector<T>& center, const Vector<T>& v) const;

		/*!
		 * \brief Get the cross product of the vector with another vector.
		 * \param v The other vector.
		 * \return The cross product.
		 */
		float crossProduct (const Vector<T>& v) const;

		/*!
		 * \brief Get the dot product of the vector with another vector.
		 * \param v The other vector.
		 * \return The dot product.
		 */
		float dotProduct (const Vector<T>& v) const;

		/*!
		 * \brief Get the rotated vector around the specified point.
		 * \param c The rotation center.
		 * \param a The rotation angle.
		 * \return The rotated vector.
		 */
		Vector<T> getRotated (const Vector<T>& c, float a) const;

		/*!
		 * \brief Get the translated vector by the specified vector.
		 * \param v The translation's vector.
		 * \return The translated vector.
		 */
		Vector<T> getTranslated (const Vector<T>& v) const;

		/*!
		 * \brief Rotate the vector around specified point.
		 * \param c The rotation center.
		 * \param a The rotation angle.
		 */
		void rotate (const Vector<T>& c, float a);

		/*!
		 * \brief Translate the vector.
		 * \param v The translation's vector.
		 */
		void translate (const Vector<T>& v);
		
		/*!
		 * \brief Normalize the vector.
		 */
		void normalize ();

		/*!
		 * \brief The '+' vector operation.
		 * \return The sum vector.
		 */
		Vector<T> operator + (const Vector<T>& v) const;

		/*!
		 * \brief The '-' vector operation.
		 * \return The result vector.
		 */
		Vector<T> operator - (const Vector<T>& v) const;

		/*!
		 * \brief The '*' vector operation.
		 * \return The scaled vector.
		 */
		Vector<T> operator * (float d) const;
		
		/*!
		 * \brief The cross product.
		 * \return The cross product.
		 */
		float operator ^ (const Vector<T>& v) const;

		/*!
		 * \brief The '/' vector operation.
		 * \return The scaled vector.
		 */
		Vector<T> operator / (float d) const;

		/*!
		 * \brief The '+=' vector operation.
		 * \return The vector's reference.
		 */
		Vector<T>& operator += (const Vector<T>& v);

		/*!
		 * \brief The '-=' vector operation.
		 * \return The vector's reference.
		 */
		Vector<T>& operator -= (const Vector<T>& v);

		/*!
		 * \brief The '*=' vector operation.
		 * \return The vector's reference.
		 */
		Vector<T>& operator *= (float d);

		/*!
		 * \brief The '/=' vector operation.
		 * \return The vector's reference.
		 */
		Vector<T>& operator /= (float d);
		
		/*!
		 * \brief Test if two vectors are equals.
		 */
		bool operator == (const Vector<T>& v);
		
		template <typename C> 
		operator Vector<C> () {
			return Vector<C> ((C) x, (C) y);
		}
};

template <typename T>
inline Vector<T>::Vector (T x, T y) {
	this->x = x;
	this->y = y;
}

template <typename T>
inline Vector<T>::Vector (const Vector<T>& v) {
	this->x = v.x;
	this->y = v.y;
}

template <typename T>
inline Vector<T>::~Vector () {
	
}

template <typename T>
inline float Vector<T>::length () const {
	T xx = this->x * this->x;
	T yy = this->y * this->y;

	return sqrt (xx + yy);
}

template <typename T>
inline float Vector<T>::angle (const Vector<T>& center) const {
	Vector<T> res = ((*this) - center);
	float a = atan2 (res.y, res.x) - atan2 (0, 0);
	if (a < 0) a += 2 * 3.14159265359;
	return a;
}

template <typename T>
inline float Vector<T>::angleBetween (const Vector<T>& center, const Vector<T>& v) const {
	float a = angle (center) - v.angle (center);
	if (a < 0) a += 2 * 3.14159265359;
	return a;
}

template <typename T>
inline float Vector<T>::crossProduct (const Vector<T>& v) const {
	return float (this->x * v.y - v.x * this->y);
}

template <typename T>
inline float Vector<T>::dotProduct (const Vector<T>& v) const {
	return (float) (this->x * v.x - this->y * v.y);
}

template <typename T>
Vector<T> Vector<T>::getRotated (const Vector<T>& c, float a) const {
	T tx = this->x - c.x,
	  ty = this->y - c.y;

	float cos_a = cos (a),
		   sin_a = sin (a);

	return Vector<T> (tx * cos_a - ty * sin_a + c.x, tx * sin_a + ty * cos_a + c.y);
}

template <typename T>
inline Vector<T> Vector<T>::getTranslated (const Vector<T>& v) const {
	return Vector<T> (this->x + v.x, this->y + v.y);
}

template <typename T>
void Vector<T>::rotate (const Vector<T>& c, float a) {
	T tx = this->x - c.x,
	  ty = this->y - c.y;

	float cos_a = cos (a),
		   sin_a = sin (a);

	this->x = tx * cos_a - ty * sin_a + c.x;
	this->y = tx * sin_a + ty * cos_a + c.y;
}

template <typename T>
inline void Vector<T>::translate (const Vector<T>& v) {
	this->x += v.x,
	this->y += v.y;
}

template <typename T>
inline void Vector<T>::normalize () {
	if (length () != 0) {
		T nx = this->x / length (), 
		  ny = this->y / length ();

		this->x = nx,
		this->y = ny;
	}
	else {
		this->x = 0;
		this->y = 0;
	}
}

template <typename T>
inline Vector<T> Vector<T>::operator + (const Vector<T>& v) const {
	return Vector<T> (this->x + v.x, this->y + v.y);
}

template <typename T>
inline Vector<T> Vector<T>::operator - (const Vector<T>& v) const {
	return Vector<T> (this->x - v.x, this->y - v.y);
}

template <typename T>
inline Vector<T> Vector<T>::operator * (float d) const {
	return Vector<T> (d * this->x, d * this->y);
}

template <typename T>
inline Vector<T> Vector<T>::operator / (float d) const {
	return Vector<T> (this->x / d, this->y / d);
}

template <typename T>
inline Vector<T>& Vector<T>::operator += (const Vector<T>& v) {
	this->x += v.x;
	this->y += v.y;

	return *this;
}

template <typename T>
inline Vector<T>& Vector<T>::operator -= (const Vector<T>& v) {
	this->x -= v.x;
	this->y -= v.y;

	return *this;
}

template <typename T>
inline Vector<T>& Vector<T>::operator *= (float d) {
	this->x *= d;
	this->y *= d;

	return *this;
}

template <typename T>
inline Vector<T>& Vector<T>::operator /= (float d) {
	this->x /= d;
	this->y /= d;

	return *this;
}

template <typename T>
float Vector<T>::operator ^ (const Vector<T>& v) const {
	return float (this->x * v.y - v.x * this->y);
}

template <typename T>
bool Vector<T>::operator == (const Vector<T>& v) {
	return x == v.x && y == v.y;
}


}}

#endif

