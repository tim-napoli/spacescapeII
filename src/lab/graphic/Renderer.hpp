#ifndef _lab_graphic_Renderer_hpp_
#define _lab_graphic_Renderer_hpp_

#include <list>
#include <map>
#include <utility>

#include "lab/math/Vector.hpp"
#include "lab/math/Box.hpp"
#include "lab/io/Video.hpp"
#include "lab/graphic/Drawable.hpp"
#include "lab/Exception.hpp"

namespace lab {
namespace graphic {

/*!
 * \brief The renderer have to write drawables to screen.
 *
 * The Renderer class will draw all drawables on the screen. It will automatically stretch the drawables from the game
 * screen size (a virtual one) to the true screen size.
 */
class Renderer {
	private:
		std::map<int, std::list<Drawable*>> mObjects; 	// The drawable objects to draw, mapped by zindex.
		math::Vector<int> mDimensions;					// The dimensions of the virtual screen.
		const io::Video* mVideo;						// The video module (Device en singleton !).
		bool mScale;									// The renderer will not conserve aspect ratio.

		int mTrembleCount;								// Number of loops the Render will tremble.
		
		ALLEGRO_TRANSFORM	mTransform;					// Base transformation.
		bool				mBarres;					// If the barres must be drawn.
		math::Box<int> 		mBarA, mBarB;				// The black bars.

	public:
		/*!
		 *
		 */
		Renderer (const math::Vector<int>& virtual_dimensions = math::Vector<int> (0, 0), 
				  const io::Video* video = NULL, bool scale = false);

		~Renderer ();

		bool hasDrawable (Drawable* addr) const;

		void addDrawable (Drawable* addr) throw (lab::Exception);

		void removeDrawable (Drawable* addr) throw (lab::Exception);

		void render ();
		
		void updateInfos ();

		void tremble (int count) {mTrembleCount = count;}
};

}}

#endif

