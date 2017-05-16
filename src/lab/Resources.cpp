#include "Resources.hpp"
#include <iostream>
#include <list>

namespace lab {

Resources::Resources (const std::string& path) {
	mBitmaps = boost::unordered_map<std::string, ALLEGRO_BITMAP*> ();
	mFonts = boost::unordered_map<std::string, ALLEGRO_FONT*> ();
	mPath = path;
}

Resources::~Resources () {
	
}

void Resources::load (const std::string& config_file_name) throw (lab::Exception) {
	config::Configuration file;
	try {
		file.load (config_file_name);
	} catch (const lab::Exception& exception) {
		throw lab::Exception (0, "Resources.load error : Cannot load file " + config_file_name + " :\n\t" + exception.getMessage ());
	}

	// Chargement des bitmaps
	auto got = file.find ("bitmaps");
	if (got != file.end ()) {
		for (auto it_v = got->second.begin (); it_v != got->second.end (); it_v++) {
			std::string path = mPath + it_v->second.getValue ();
			ALLEGRO_BITMAP* bmp = al_load_bitmap (path.c_str ());
			if (bmp == NULL) {
				throw lab::Exception (0, "Resources.load error : Cannot find bitmap \"" + it_v->first + "\" at " + path + ".");
			}
			al_convert_mask_to_alpha (bmp, al_map_rgb (255, 0, 255));
			mBitmaps.emplace (it_v->first, bmp);
		}
	}

	// Chargement des fonts (A améliorer)
	got = file.find ("fonts");
	if (got != file.end ()) {
		for (auto it_v = got->second.begin (); it_v != got->second.end (); it_v++) {
			// Traitement du tuple
			std::string value = it_v->second.getValue ();
			size_t pos_sep = value.find (';');
			if (pos_sep == std::string::npos) {
				throw lab::Exception (0, "Resources.load error : Bad font declaration \"" + it_v->first + "\" at " + mPath + ".");
			}
			std::string size = value.substr (pos_sep + 1, value.length () - (pos_sep + 1));
			util::Value conv = util::Value (size);
			std::string path = mPath + value.substr (0, pos_sep);

			// Chargement de la font
			ALLEGRO_FONT* font = al_load_ttf_font (path.c_str (), conv.getValue<int> (), 0);
			if (font == NULL) {
				throw lab::Exception (0, "Resources.load error : Cannot find font \"" + it_v->first + "\" at " + path + ".");
			}
			mFonts.emplace (it_v->first, font);
		}
	}
	
	// Chargement des samples
	// On choisit de ne pas considérer le non chargement d'un sample comme une erreur.
	got = file.find ("samples");
	if (got != file.end ()) {
		for (auto it_v = got->second.begin (); it_v != got->second.end (); it_v++) {
			// Chargement du ALLEGRO_SAMPLE
			std::string path = mPath + it_v->second.getValue ();
			ALLEGRO_SAMPLE* al_sample = al_load_sample (path.c_str ());
			if (al_sample == NULL) {
				std::cout << "Resources.load warning : Cannot load sample " << it_v->first << " at " << path << "." << std::endl;
			}
			else {
				mSamples.emplace (it_v->first, new sound::Sample (al_sample));
			}
		}
	}
	
	// Chargement des streams
	got = file.find ("streams");
	if (got != file.end ()) {
		for (auto it_v = got->second.begin (); it_v != got->second.end (); it_v++) {
			// Chargement du sound::Stream
			std::string path = mPath + it_v->second.getValue ();
			sound::Stream* stream = sound::Stream::load (path);
			if (stream == NULL) {
				std::cout << "Resources.load warning : Cannot load stream " << it_v->first << " at " << path << "." << std::endl;
			}
			else {
				mStreams.emplace (it_v->first, stream);
			}
		}
	}
}

void Resources::unload () {
	for (auto it = mBitmaps.begin (); it != mBitmaps.end (); it++) {
		al_destroy_bitmap (it->second);
	}

	for (auto it = mFonts.begin (); it != mFonts.end (); it++) {
		al_destroy_font (it->second);
	}
	
	for (auto it = mSamples.begin (); it != mSamples.end (); it++) {
		delete it->second;
	}
	
	for (auto it = mStreams.begin (); it != mStreams.end (); it++) {
		delete it->second;
	}
}

ALLEGRO_BITMAP* Resources::getBitmap (const std::string& name) {
	auto got = mBitmaps.find (name);

	if (got == mBitmaps.end ()) {
		return NULL;
	}

	return got->second;
}

ALLEGRO_FONT* Resources::getFont (const std::string& name) {
	auto got = mFonts.find (name);

	if (got == mFonts.end ()) {
		return NULL;
	}

	return got->second;
}

sound::Sample* Resources::getSample (const std::string& name) {
	auto got = mSamples.find (name);
	
	if (got == mSamples.end ()) {
		return NULL;
	}
	
	return got->second;
}

sound::Stream* Resources::getStream (const std::string& name) {
	auto got = mStreams.find (name);
	
	if (got == mStreams.end ()) {
		return NULL;
	}
	
	return got->second;
}

}

