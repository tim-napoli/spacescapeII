#ifndef _lab_sound_Stream_hpp_
#define _lab_sound_Stream_hpp_

#include <string>

#include <allegro5/allegro_audio.h>

#include "lab/Exception.hpp"

namespace lab {
namespace sound {

class Stream {
	private:
		ALLEGRO_AUDIO_STREAM* mStream;
	
	public:
		Stream (ALLEGRO_AUDIO_STREAM* stream);
		
		~Stream ();
		
		void play (bool loop);
		
		void stop ();
		
		void rewind () {al_rewind_audio_stream (mStream);}
		
		bool playing () const {return al_get_audio_stream_playing (mStream);}
		
		ALLEGRO_AUDIO_STREAM* getStream () const {return mStream;}
		
		static Stream* load (const std::string& filename) throw (lab::Exception);
};

}}

#endif

