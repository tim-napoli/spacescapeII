#ifndef _lab_math_Polygon_hpp_
#define _lab_math_Polygon_hpp_

#include <cstdarg>
#include <cmath>

#include "lab/math/Vector.hpp"
#include "lab/math/Segment.hpp"
#include "lab/Exception.hpp"

namespace lab {
namespace math {

template <typename T>
class Polygon {
	protected:
		unsigned int mOrder;
		Vector<T>	 mIsoCentroid;
		std::vector<Vector<T>>   mVertex;
		
		/*!
		 * \brief Update the iso-centroïd.
		 */
		void calculIsoCentroid ();
		
	public:
		/*!
		 * \brief Constructor.
		 * \param order The order of the polygon. 
		 */
		Polygon (unsigned int order = 3);
		
		/*!
		 * \brief Copy constructor.
		 * \param poly_number The polygon to copy. 
		 */
		Polygon (const Polygon<T>& poly);
		
		/*!
		 * \brief Destructor.
		 */
		virtual ~Polygon ();
		
		
		/*!
		 * \brief Set a vertice.
		 * \param index The index of the vertex to set. 
		 * \param e The vertice.
		 *
		 * This method will automaticly update the iso-centroïd.
		 */
		void setEdge (int index, const Vector<T>& e);
		
		/*!
		 * \brief Set a vertice.
		 * \param index The index of the vertex to set. 
		 * \param e The vertice.
		 * \param update_isocentroid Update the iso-centroïd if it is true.
		 */
		void setEdge (int index, const Vector<T>& e, bool update_isocentroid);
		
		
		/*!
		 * \brief Translate the poly.
		 * \param v The translation vector. 
		 */
		void translate (const Vector<T>& v);
		
		/*!
		 * \brief Rotate the poly.
		 * \param c The rotation center. 
		 * \param angle The rotation angle.
		 */
		void rotate (const Vector<T>& c, float angle);
		
		/*!
		 * \brief Get a translated copy of the poly.
		 * \param v The translation vector. 
		 * \return A new translated poly.
		 */
		Polygon<T> getTranslated (const Vector<T>& v) const;
		
		/*!
		 * \brief Get a rotated copy of the poly.
		 * \param v The rotation center. 
		 * \param angle The rotation angle.
		 * \return A new rotated poly.
		 */
		Polygon<T> getRotated (const Vector<T>& c, float angle) const;
		
		
		/*!
		 * \brief Get the order of the poly.
		 * \return The order.
		 */
		unsigned int getOrder () const {return mOrder;}
		
		/*!
		 * \brief Get the surface of the poly.
		 * \return The surface of the poly.
		 */
		float getSurface () const;
		
		/*!
		 * \brief Get the perimeter of the poly.
		 * \return The perimeter of the poly.
		 */
		float getPerimeter () const;
		
		/*!
		 * \brief Get the iso-centroïd of the poly.
		 * \return The iso-centroïd of the poly.
		 */
		const Vector<T>& getIsoCentroid () const {return mIsoCentroid;}
		
		
		/*!
		 * \brief Check if the vector coordinates are in the polygon.
		 * \param v The vector to check.
		 * \return True if it is.
		 */
		bool contains (const Vector<T>& v, float precision) const;
		
		/*!
		 * \brief Check if a polygon is intersecting this polygon.
		 * \param poly The polygon to check.
		 * \return True if it is.
		 */
		bool intersects (const Polygon<T>& poly, float precision) const;
		
		/*!
		 * \brief Get the intersection of two polygons.
		 * \param poly The other polygon.
		 * \return The intersection as a new polygon.
		 * \throw lab::Exception if there is no intersection.
		 */
		Polygon<T> getIntersection (const Polygon<T>& poly, float precision) const throw (lab::Exception);
		
		/*!
		 * \brief Get the vertex by its index.
		 * \param index The index of the vertice.
		 * \return The vertice.
		 * \throw lab::Exception if this index is upper than the number of vertex of this polygon.
		 */
		const Vector<T>& operator [] (int index) const {return mVertex [index];}
		Vector<T>& operator [] (int index) {return mVertex [index];}
};

template <typename T>
void Polygon<T>::calculIsoCentroid () {
	mIsoCentroid.x = 0;
	mIsoCentroid.y = 0;

	for (auto it = mVertex.begin (); it != mVertex.end (); it++) {
		mIsoCentroid += *it;
	}
	
	mIsoCentroid /= mOrder;
}

template <typename T>
Polygon<T>::Polygon (unsigned int order) {
	mOrder = order;
	mVertex.resize (order);
}

template <typename T>
Polygon<T>::Polygon (const Polygon<T>& poly) {
	mOrder = poly.getOrder ();
	mVertex.resize (mOrder);
	
	for (int i = 0; i < mOrder; i++) {
		mVertex [i] = poly [i];
	}
	
	calculIsoCentroid ();
}

template <typename T>
Polygon<T>::~Polygon () {

}

template <typename T>
void Polygon<T>::setEdge (int index, const Vector<T>& e) {
	mVertex [index] = e;
	calculIsoCentroid ();
}

template <typename T>
void Polygon<T>::setEdge (int index, const Vector<T>& e, bool update_isocentroid) {
	mVertex [index] = e;
	if (update_isocentroid) {
		calculIsoCentroid ();
	}
}

template <typename T>
void Polygon<T>::translate (const Vector<T>& v) {
	mIsoCentroid += v;
	for (int i = 0; i < mOrder; i++) {
		mVertex [i] += v;
	}
}

template <typename T>
void Polygon<T>::rotate (const Vector<T>& c, float angle) {
	mIsoCentroid.rotate (c, angle);
	for (auto it = mVertex.begin (); it != mVertex.end (); it++) {
		it->rotate (c, angle);
	}
}

template <typename T>
Polygon<T> Polygon<T>::getTranslated (const Vector<T>& v) const {
	Polygon<T> poly (*this);
	poly.translate (v);
	return poly;
}

template <typename T>
Polygon<T> Polygon<T>::getRotated (const Vector<T>& c, float angle) const {
	Polygon<T> poly (*this);
	poly.rotate (c, angle);
	return poly;
}

template <typename T>
inline float __triangle_surface (const Vector<T>& a, const Vector<T>& b, const Vector<T>& c) {
	return std::abs ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y)) / 2;
}

template <typename T>
float Polygon<T>::getSurface () const {
	float surface = 0.0f;

	for (int i = 0; i < mOrder - 1; i++) {
		surface += __triangle_surface (mIsoCentroid, mVertex [i], mVertex [i + 1]);
	}
	
	return surface;
}

template <typename T>
float Polygon<T>::getPerimeter () const {
	float p = 0.0f;

	for (int i = 0; i < mOrder - 1; i++) {
		p += (mVertex [i + 1] - mVertex [i]).length ();
	}
	
	return p;
}

template <typename T>
inline float __in_triangle (const Vector<T>& t, const Vector<T>& a, const Vector<T>& b, const Vector<T>& c, float precision) {
	float sa = __triangle_surface (t, a, b);
	float sb = __triangle_surface (t, b, c);
	float sc = __triangle_surface (t, c, a);
	float sum = sa + sb + sc;
	float surface = __triangle_surface (a, b, c);
	
	return (surface >= sum - precision && surface <= sum + precision);
}

template <typename T>
bool Polygon<T>::contains (const Vector<T>& v, float precision) const {
	for (int i = 0; i < mOrder - 1; i++) {
		if (__in_triangle (v, mIsoCentroid, mVertex [i], mVertex [i + 1], precision)) {
			return true;
		}
	}
	
	return false;
}

template <typename T>
bool Polygon<T>::intersects (const Polygon<T>& poly, float precision) const {
	// On va d'abords regarder si au moins un point de poly se trouve dans ce polygône.
	for (int i = 0; i < poly.getOrder (); i++) {
		if (contains (poly [i], precision)) {
			return true;
		}
	}
	
	// Puis si non, on va regarder si au moins un coté de poly a une intersection avec un coté du polygône.
	for (int i = 0; i < poly.getOrder () - 1; i++) {
		Segment<T> seg_poly (poly [i], poly [i + 1]);
		for (int j = 0; j < mOrder - 1; j++) {
			Segment<T> seg_this (mVertex [j], mVertex [j + 1]);
			if (seg_this.intersects (seg_poly)) {
				return true;
			}
		}
	}
	
	return false;
}

template <typename T>
Polygon<T> Polygon<T>::getIntersection (const Polygon<T>& poly, float precision) const throw (lab::Exception) {
	std::vector<Vector<T>> intersection_points;
	intersection_points.reserve (mOrder + poly.getOrder ());

	// On va d'abords récupérer les points de poly dans celui-ci et de celui-ci dans poly.
	for (int i = 0; i < poly.getOrder (); i++) {
		if (contains (poly [i], precision)) {
			intersection_points.push_back (poly [i]);
		}
	}
	for (int i = 0; i < mOrder; i++) {
		if (poly.contains (mVertex [i], precision)) {
			intersection_points.push_back (mVertex [i]);
		}
	}
	
	// Puis les points d'intersection entre poly avec celui-ci et de celui-ci avec poly.
	for (int i = 0; i < poly.getOrder () - 1; i++) {
		Segment<T> seg_poly (poly [i], poly [i + 1]);
		for (int j = 0; j < mOrder - 1; j++) {
			Segment<T> seg_this (mVertex [j], mVertex [j + 1]);
			Vector<T> out;
			if (seg_this.intersects (seg_poly, out, precision)) {
				intersection_points.push_back (out);
			}
		}
		Segment<T> seg_this (mVertex [mOrder - 1], mVertex [0]);
		Vector<T> out;
		if (seg_this.intersects (seg_poly, out, precision)) {
			intersection_points.push_back (out);
		}
	}
	// Le petit dernier
	Segment<T> seg_poly (poly [poly.getOrder () - 1], poly [0]);
	for (int j = 0; j < mOrder - 1; j++) {
		Segment<T> seg_this (mVertex [j], mVertex [j + 1]);
		Vector<T> out;
		if (seg_this.intersects (seg_poly, out, precision)) {
			intersection_points.push_back (out);
		}
	}
	Segment<T> seg_this (mVertex [mOrder - 1], mVertex [0]);
	Vector<T> out;
	if (seg_this.intersects (seg_poly, out, precision)) {
		intersection_points.push_back (out);
	}
	
	// Suppression des doublons
	int npoints = intersection_points.size ();
	for (int i = 0; i < npoints - 1; i++) {
		for (int j = i + 1; j < npoints; j++) {
			if (intersection_points [i] == intersection_points [j]) {
				for (int k = j; k < npoints - 1; k++) {
					intersection_points [k] = intersection_points [k + 1];
				}
				
				j--;
				npoints--;
				intersection_points.resize (npoints);
			}
		}
	}
	
	// Intermède
	if (npoints <= 0) {
		//std::cout << "Fuck" << std::endl;
		throw lab::Exception (0, "Polygon::getIntersection warning : no Intersection.");
	}
	
	// On calcule l'isobarycentre du polygone obtenu.
	Vector<T> babar;
	for (auto it = intersection_points.begin (); it != intersection_points.end (); it++) {
		babar += *it;
	}
	babar /= (T) npoints;
	
	// On trie la liste de manière à ce que les coordonnées des vecteurs suivent une rotation dans le sens anti-horaire
	// avec pour centre l'isobarycentre.
	for (int i = 1; i < intersection_points.size () - 1; i++) {
		float angle_i = intersection_points [i].angleBetween (babar, intersection_points [0]);
		for (int j = i + 1; j < intersection_points.size (); j++) {
			float angle_j = intersection_points [j].angleBetween (babar, intersection_points [0]);
			if (angle_j < angle_i) {
				angle_i = angle_j;
				Vector<T> tmp = intersection_points [j];
				intersection_points [j] = intersection_points [i];
				intersection_points [i] = tmp;
			}
		}
	}
	
	// Et paf !
	Polygon<T> result (npoints);
	for (int i = 0; i < npoints - 1; i++) {
		result.setEdge (i, intersection_points [i], false);
	}
	result.setEdge (npoints - 1, intersection_points [npoints - 1], true);
	
	return result;
}

}}

#endif

