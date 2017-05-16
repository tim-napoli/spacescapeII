#ifndef _lab_graphic_Sprite_hpp_
#define _lab_graphic_Sprite_hpp_

#include <allegro5/allegro.h>
#include "lab/graphic/Drawable.hpp"

namespace lab {
namespace graphic {

/*!
 * \brief A Sprite is a Drawable that is destinated to draw images.
 *
 * A sprite is a special Drawable for drawing images. 
 */
class Sprite : public Drawable {
	protected:
		int mFlags;
		ALLEGRO_BITMAP* mBitmap;

	public:
		/*!
		 * \brief The FLIP_X sprite's Flag.
		 */
		static int FLIP_X;

		/*!
		 * \brief The FLIP_Y sprite's Flag.
		 */
		static int FLIP_Y;

		/*!
		 * \brief Constructor.
		 * \param position The sprite position.
		 * \param dimensions The sprite dimensions.
		 * \param zindex The sprite zindex.
		 * \param hot_point The sprite hot point.
		 * \param angle The rotation angle of the sprite (in radiants).
		 * \param flags The sprite flags.
		 * \param bitmap The sprite bitmap.
		 */
		Sprite (const math::Vector<int>& position, const math::Vector<int>& dimensions, const math::Vector<int>& hot_point, float angle, int zindex, 
				int flags, ALLEGRO_BITMAP* bitmap);

		/*!
		 * \brief Destructor.
		 */
		~Sprite ();

		/*!
		 * \brief Set the Sprite flags.
		 * \param flags The flags of the Sprite.
		 */
		void setFlags (int flags) {mFlags = flags;}

		/*!
		 * \brief Get the sprite flags.
		 * \return The flags of the Sprite.
		 */
		int getFlags () const {return mFlags;}

		/*!
		 * \brief Will draw the Sprite.
		 *
		 * This method will draw the sprite. If the sprite flags is set to FLIP_X, then sprite will be horizontaly flipped,
		 * and if flags is set to FLIP_Y, then the sprite will be vertically flipped (it can be flipped on both sides).
		 * The sprite will be rotated around its center. It will be stretched to the size of its Box.
		 */
		virtual void draw () const;
};

}}

#endif

