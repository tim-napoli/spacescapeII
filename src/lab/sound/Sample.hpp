#ifndef _lab_sound_Sample_hpp_
#define _lab_sound_Sample_hpp_

#include <allegro5/allegro_audio.h>

namespace lab {
namespace sound {

/*!
 * \brief A simple ALLEGRO_SAMPLE wrapper.
 */
class Sample {
	private:
		ALLEGRO_SAMPLE* 	mSample;
		ALLEGRO_SAMPLE_ID   mPlayingId;	// Must stop the sample in case of looped playing (-1 if no play).

	public:
		/*!
		 * \brief Constructor.
		 * \param sample The ALLEGRO_SAMPLE to wrap.
		 * \param gain The gain of the sample (1.0 is normal).
		 * \param pan The pan of the sample (between -1.0 and 1.0).
		 * \param speed The playing speed (1.0 is normal).
		 */
		 Sample (ALLEGRO_SAMPLE* sample);
		 
		 /*!
		  * \brief Destructor.
		  */
		 ~Sample ();
		 
		 /*!
		 * \brief Play the sample.
		 * \param gain The gain of the sample (1.0 is normal).
		 * \param pan The pan of the sample (between -1.0 and 1.0).
		 * \param speed The playing speed (1.0 is normal).
		 * \param loop Will be played till it is not stopped.
		 *
		 * If the sample has not been loaded, it will simply not be played.
		 */
		 void play (float gain, float pan, float speed, bool loop);
		 
		 /*!
		  * \brief Stop the sample.
		  */
		 void stop ();
		 
		 
};

}}

#endif

