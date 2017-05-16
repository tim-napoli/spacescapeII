#include "io/Sound.hpp"
#include <iostream>

namespace lab {
namespace io {

Sound::Sound () : Device ("sound"), config::Configurable () {
	mMixer = NULL;
	mVoice = NULL;
}

Sound::~Sound () {

}

void Sound::initialize () throw (lab::Exception) {
	// Installation de l'add-on audio de Allegro.
	if (!al_install_audio ()) {
		throw lab::Exception (0, "Sound::initialize error : Cannot install audio.");
	}
	
	// Initialisation de l'add-on de codecs.
	if (!al_init_acodec_addon ()) {
		std::cout << "Sound::initialize warning : Cannot load the acodec addon. Only few audio types will be loadables." << std::endl;
	}
	
	mVoice = al_create_voice (44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_1);
	
	// Création du mixer (Utiliser un mixer personnel plutôt ?).
	//mMixer = al_create_mixer (44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_1);
	//al_attach_mixer_to_voice (mMixer, mVoice);
	//al_set_default_mixer (mMixer);
	al_reserve_samples (mConfig.getValue ("sound", "max_sounds", util::Value ("32")).getValue<int> ());
	
	// Configuration du mixer.
	unsigned int freq = mConfig.getValue ("sound", "frequence", util::Value ("44100")).getValue<unsigned int> ();
	al_set_mixer_frequency (al_get_default_mixer (), freq);
	
	float volume = mConfig.getValue ("sound", "volume", util::Value ("1.0")).getValue<float> ();
	al_set_mixer_gain (al_get_default_mixer (), volume);
}

void Sound::shutdown () {
	//al_destroy_mixer (mMixer);
	//al_destroy_voice (mVoice);
	al_uninstall_audio ();
}

void Sound::handleInput () {

}

void Sound::cycle () {

}

}}

