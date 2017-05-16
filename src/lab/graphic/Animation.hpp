#ifndef _lab_graphic_Animation_hpp_
#define _lab_graphic_Animation_hpp_

#include <vector>

#include "lab/math/Vector.hpp"
#include "lab/graphic/Drawable.hpp"

namespace lab {
namespace graphic {

class Animation : public Drawable {
	public:
		static const int MODE_LOOP 	= 0; /*! Will go from the last frame to the first. */
		static const int MODE_REVERSE = 1; /*! At the end of the animation, the animation will play in reverse mode (speed = -1), and then and then... */
		static const int MODE_SINGLE = 2; /*! At the end of the animation, the animation will stop... */

	private:
		int mTickRatio, mSpeed, mCounter;
		unsigned int mCurrentFrame;
		int mMode;
		std::vector<Drawable*> mDrawables;

	public:
		Animation (const math::Vector<int>& position, float angle, int zindex, int tick_ratio, int mode, int num_frames);

		~Animation ();

		void setFrame (int n, Drawable* drawable) {mDrawables [n] = drawable;}
		
		void setMode (int mode) {mMode = mode;}

		bool isLastFrame () const {return mCurrentFrame == (unsigned int) (mDrawables.size () - 1);}

		void update ();

		void draw () const;
};

}}

#endif

