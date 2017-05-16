#ifndef _lab_graphic_Text_hpp_
#define _lab_graphic_Text_hpp_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>

#include "lab/graphic/Drawable.hpp"
#include "lab/math/Vector.hpp"

namespace lab {
namespace graphic {

/*!
 * \brief A Sprite is a Drawable that is destinated to draw images.
 *
 * A sprite is a special Drawable for drawing images. 
 */
class Text : public Drawable {
	public:
		const static int ALIGN_LEFT = ALLEGRO_ALIGN_LEFT;
		const static int ALIGN_RIGHT = ALLEGRO_ALIGN_RIGHT;
		const static int ALIGN_CENTER = ALLEGRO_ALIGN_CENTER;

	private:
		ALLEGRO_FONT* mFont;
		ALLEGRO_COLOR mColor;
		ALLEGRO_USTR* mText;
		
		int mFlags;

	public:
		/*!
		 * \brief Constructor.
		 * \param position The sprite position.
		 * \param dimensions The sprite dimensions.
		 * \param zindex The sprite zindex.
		 * \param hot_point The sprite hot point.
		 * \param angle The rotation angle of the sprite (in radiants).
		 * \param font The text font.
		 * \param color The text color.
		 * \param text The text text.
		 * \param flags The text flags.
		 */
		Text (const math::Vector<int>& position, const math::Vector<int>& hot_point, float angle, int zindex, 
				ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::string text, int flags);
				
		Text (const math::Vector<int>& position, const math::Vector<int>& hot_point, float angle, int zindex, 
			  ALLEGRO_FONT* font, ALLEGRO_COLOR color, ALLEGRO_USTR* text, int flags);

		/*!
		 * \brief Destructor.
		 */
		~Text ();
		
		void setText (const std::string& str) {al_ustr_free (mText); mText = al_ustr_new (str.c_str ());}
		
		void setColor (ALLEGRO_COLOR color) {mColor = color;}
		
		ALLEGRO_USTR* getText () {return mText;}

		/*!
		 * \brief Will draw the Text.
		 */
		void draw () const;
};

}}

#endif

