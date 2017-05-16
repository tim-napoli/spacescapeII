#include "lab/sound/Stream.hpp"


namespace lab {
namespace sound {

Stream::Stream (ALLEGRO_AUDIO_STREAM* stream) {
	mStream = stream;
}

Stream::~Stream () {
	al_destroy_audio_stream (mStream);
}

void Stream::play (bool loop) {
	al_set_audio_stream_playmode ( mStream, loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE );
	al_set_audio_stream_playing ( mStream, true );
}

void Stream::stop () {
	al_set_audio_stream_playing ( mStream, false );
}

Stream* Stream::load (const std::string& filename) throw (lab::Exception) {
	ALLEGRO_AUDIO_STREAM *stream = al_load_audio_stream ( filename.c_str (), 10, 1024 );
	if (stream == NULL) {
		throw lab::Exception (0, "Stream::load error : cannot load stream " + filename + ".");
	}	
	al_set_audio_stream_playmode ( stream, ALLEGRO_PLAYMODE_ONCE );
	al_set_audio_stream_playing ( stream, false );
	al_attach_audio_stream_to_mixer (stream, al_get_default_mixer ());
	return new Stream (stream);
}

}}

