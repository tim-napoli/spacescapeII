#ifndef _lab_graphic_Drawable_hpp_
#define _lab_graphic_Drawable_hpp_

#include <allegro5/allegro.h>

#include "lab/math/Vector.hpp"

namespace lab {
namespace graphic {

/*!
 * \brief This is the base class for objects that will be drawed by the Renderer.
 *
 * A Drawable is an object which can be drawn by the Renderer. It will contains display informations (like position,
 * rotation, hot point, angle), and a zindex, which will be used by the renderer to determinate when display this
 * Drawable.
 * The "draw" method must be implemented by the inherited classes.
 * The hot point is the point of the Drawable which will be drawn at its position.
 */
class Drawable {
	private:
		int mZindex;

	protected:
		math::Vector<int> mPosition;
		math::Vector<int> mDimensions;
		math::Vector<int> mHotPoint;
		float mAngle;

	public:
		/*!
 		 * \brief Constructor.
		 * \param position The position of this Drawable.
		 * \param dimensions The dimensions.
		 * \param hot_point The hot point.
		 * \param angle The angle in radients.
		 * \param zindex The zindex.
		 */
		Drawable (const math::Vector<int>& position = math::Vector<int> (), 
				  const math::Vector<int>& dimensions = math::Vector<int> (),
				  const math::Vector<int>& hot_point = math::Vector<int> (),
				  float angle = 0.0f,
				  int zindex = 0);

		/*!
		 * \brief Destructor.
		 */
		virtual ~Drawable ();

		/*!
		 * \brief Get the zindex of this Drawable.
		 * \return The zindex of this Drawable.
		 */
		int getZindex () const {return mZindex;}

		/*!
		 * \brief Set the zindex of this Drawable.
		 * \param zindex The new zindex of this Drawable.
		 */
		void setZindex (int zindex) {mZindex = zindex;}

		/*!
		 * \brief Get the Drawable's position, assuming the Hot Point.
		 * \return The Drawable's position.
		 */
		math::Vector<int> getPosition () const {return mPosition - mHotPoint;}

		/*!
		 * \brief Set the Drawable's position, assuming the Hot Point.
		 * \param position The new Drawable's position.
		 */
		void setPosition (const math::Vector<int>& position) {mPosition = position + mHotPoint;}

		/*!
		 * \brief Get the Drawable's Hot Point.
		 * \return The Drawable's hot point.
		 */
		math::Vector<int> getHotPoint () const {return mHotPoint;}

		/*!
		 * \brief Set the Drawable's hot point.
		 * \param hot_point The new hot point.
		 */
		void setHotPoint (const math::Vector<int>& hot_point) {mHotPoint = hot_point;}

		/*!
		 * \brief Get the Drawable's dimensions.
		 * \return The Drawable's dimensions.
		 */
		math::Vector<int> getDimensions () const {return mDimensions;}

		/*!
		 * \brief Set the Drawable's dimensions.
		 * \param position The new Drawable's dimensions.
		 */
		void setDimensions (const math::Vector<int>& dimensions) {mDimensions = dimensions;}

		/*!
		 * \brief Get the Drawable's angle.
		 * \return The Drawable's angle (in radients).
		 */
		float getAngle () const {return mAngle;}

		/*!
		 * \brief Set the Drawable's angle.
		 * \param position The new Drawable's angle.
		 */
		void setAngle (float angle) {mAngle = angle;}

		/*!
		 * \brief Will setting a transformation through which each drawing operation will pass (for translate, rotate...).
		 */
		virtual void getReady ();

		/*!
		 * \brief This method will contains instructions to draw this Drawable.
		 */
		virtual void draw () const = 0;
};

}}

#endif

