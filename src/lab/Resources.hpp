#ifndef _lab_Resources_hpp_
#define _lab_Resources_hpp_

#include <boost/unordered_map.hpp>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>

#include "lab/config/Configuration.hpp"
#include "lab/sound/Sample.hpp"
#include "lab/sound/Stream.hpp"
#include "lab/Exception.hpp"

namespace lab {

/*!
 * \brief The resources class contains resources used by a game.
 *
 * The Resources class will be loaded from a config::Configuration object, containing these sections :
 * - bitmaps (v)
 * - sounds  (v)
 * - musics  (v)
 * - fonts	 (v)
 * - shaders (v)
 * Each resource is designed by a name associated to a path (the path of the resource file). Exemple :
 * player = "player.bmp"
 */
class Resources {
	private:
		std::string mPath;
		boost::unordered_map<std::string, ALLEGRO_BITMAP*> mBitmaps;
		boost::unordered_map<std::string, ALLEGRO_FONT*> mFonts;
		boost::unordered_map<std::string, sound::Sample*> mSamples;
		boost::unordered_map<std::string, sound::Stream*> mStreams;

	public:
		/*!
		 * \brief Resources constructor.
		 * \param path The directory where resources are stocked.
		 */
		Resources (const std::string& path = "");

		/*!
		 * \brief Resources destructor.
		 */
		~Resources ();

		/*!
		 * \brief Load the data from a config::Configuration.
		 * \param config_file_name The name of the configuration file to use to load datas.
		 * \throw lab::Exception If a data cannot be loaded.
		 *
		 */
		void load (const std::string& config_file_name) throw (lab::Exception);

		/*!
		 * \brief Free all data used by the Resources.
		 */
		void unload ();

		/*!
		 * \brief Get a Bitmap.
		 * \param name The name of the Bitmap.
		 * \return NULL if the data is not exist.
		 */
		ALLEGRO_BITMAP* getBitmap (const std::string& name);

		/*!
		 * \brief Get a Font.
		 * \param name The name of the Font.
		 * \return NULL if the data is not exist.
		 */
		ALLEGRO_FONT* getFont (const std::string& name);
		
		/*!
		 * \brief Get a Sample.
		 * \param name The name of the Sample.
		 * \return NULL if the sample does not exist.
		 */
		sound::Sample* getSample (const std::string& name);
		
		/*!
		 * \brief Get a Stream.
		 * \param name The name of the Stream.
		 * \return NULL if the stream does not exist.
		 */
		sound::Stream* getStream (const std::string& name);
};

}

#endif

