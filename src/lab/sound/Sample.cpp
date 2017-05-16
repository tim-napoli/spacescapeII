#include "sound/Sample.hpp"

namespace lab {
namespace sound {

Sample::Sample (ALLEGRO_SAMPLE* sample) {
	mSample = sample;
}

Sample::~Sample () {
	if (mSample) {
 		al_destroy_sample (mSample);
 	}
}

void Sample::play (float gain, float pan, float speed, bool loop) {
	if (mSample != NULL) {
		al_play_sample (mSample, gain, pan, speed, loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE, &mPlayingId);
	}
}

void Sample::stop () {
	al_stop_sample (&mPlayingId);
}

}}

