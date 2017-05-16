#ifndef _lab_Segment_hpp_
#define _lab_Segment_hpp_

#include "lab/math/Vector.hpp"

namespace lab {
namespace math {

template <typename T>
class Segment {
	public:
		Vector<T> A, B; /*! The segment points. */
	
	
		/*!
		 * \brief Constructor.
		 * \param A, B The two vectors (points) of the segment.
		 */ 
		Segment (const Vector<T>& A, const Vector<T>& B);
		
		/*!
		 * \brief Copy constructor.
		 * \param s The segment to copy.
		 */
		Segment (const Segment& s);
		
		/*!
		 * \brief Destructor.
		 */
		virtual ~Segment ();
		
		
		/*!
		 * \brief Translate the vector.
		 * \param v The translation vector.
		 */
		void translate (const Vector<T>& v);
		
		/*!
		 * \brief Rotate the vector.
		 * \param c The rotation center.
		 * \param angle The rotation angle.
		 */
		void rotate (const Vector<T>& c, float angle);
		
		/*!
		 * \brief Get a translated copy of this segment.
		 * \param v The translation vector.
		 * \return A tranlsated copy of this segment.
		 */
		Segment<T> getTranslated (const Vector<T>& v) const;
		
		/*!
		 * \brief Get a rotated copy of this segment.
		 * \param c The rotation center.
		 * \param angle The rotation angle.
		 * \return A rotated copy of this segment.
		 */
		Segment<T> getRotated (const Vector<T>& c, float angle) const;
		
		
		/*!
		 * \brief Check if the segment contains a point.
		 * \param p The point.
		 * \return true if the point is on the segment.
		 */
		bool contains (const Vector<T>& p) const;
		
		/*!
		 * \brief Check if it exists an intersection between the two segments.
		 * \param s The other segment.
		 */
		bool intersects (const Segment<T>& s, Vector<T>& out, float precision) const;
		
		/*!
		 * \brief Check if it exists an intersection between the two segments.
		 * \param s The other segment.
		 */
		bool intersects (const Segment<T>& s) const;
				
};

template <typename T>
Segment<T>::Segment (const Vector<T>& A, const Vector<T>& B) {
	this->A = A;
	this->B = B;
}

template <typename T>
Segment<T>::Segment (const Segment& s) {
	A = s.A;
	B = s.B;
}

template <typename T>
Segment<T>::~Segment () {

}

template <typename T>
void Segment<T>::translate (const Vector<T>& v) {
	A += v;
	B += v;
}

template <typename T>
void Segment<T>::rotate (const Vector<T>& c, float angle) {
	A.rotate (c, angle);
	B.rotate (c, angle);
}

template <typename T>
Segment<T> Segment<T>::getTranslated (const Vector<T>& v) const {
	Segment<T> s = *this;
	
	s.A += v;
	s.B += v;
	
	return s;
}

template <typename T>
Segment<T> Segment<T>::getRotated (const Vector<T>& c, float angle) const {
	Segment<T> s = *this;
	
	s.A.rotate (c, angle);
	s.B.rotate (c, angle);
	
	return s;
}

template <typename T>
bool Segment<T>::contains (const Vector<T>& p) const {
	float pA = (p - A).length ();
	float pB = (p - B).length ();
	float AB = (A - B).length ();
	
	return (pA + pB == AB);
}

template <typename T>
bool Segment<T>::intersects (const Segment<T>& seg, Vector<T>& out, float precision) const {
	Vector<T> r, s;
	
	r = B - A;
	s = seg.B - seg.A;
	
	if (r ^ s == 0) {
		return false;
	}
	
	float t = ((seg.A - A) ^ s) / (r ^ s);
	float u = ((seg.A - A) ^ r) / (r ^ s);

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
		float Artx = (A + r * t).x;
		float Arty = (A + r * t).y;
		float Bsux = (seg.A + s * u).x;
		float Bsuy = (seg.A + s * u).y;
	
		if (Artx >= Bsux - precision && Artx <= Bsux + precision && 
			Arty >= Bsuy - precision && Arty <= Bsuy + precision) {
			out = A + r * t;
			return true;
		}
	}
	
	return false;
}

template <typename T>
bool Segment<T>::intersects (const Segment<T>& seg) const {
	Vector<T> r, s;
	
	r = B - A;
	s = seg.B - seg.A;
	
	if ((r ^ s) == 0) {
		return false;
	}
	
	float t = ((seg.A - A) ^ s) / (r ^ s);
	float u = ((seg.A - A) ^ r) / (r ^ s);
	
	if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
		if (A + r * t == seg.A + s * u) {
			return true;
		}
	}
	
	return false;
}

}}

#endif

