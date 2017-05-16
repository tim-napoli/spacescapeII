#include <string>
#include <sstream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>
#include <GL/glu.h>

#include "event/Event.hpp"
#include "util/Value.hpp"
#include "io/Video.hpp"

namespace lab {
namespace io {

Video::Video (const std::string& window_name) : AllegroDevice ("Video"), config::Configurable () {
	mWindowName = window_name;

	mDisplay = NULL;
}

Video::~Video () {

}

void Video::initialize () throw (lab::Exception) {
	AllegroDevice::initialize ();

	// mConfiguring the flags and options of the display.
	int sample_level = mConfig.getValue ( "video", "sample_level", util::Value ("0") ).getValue<int> ();
	if (sample_level > 0) {
		al_set_new_display_option (ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
		al_set_new_display_option (ALLEGRO_SAMPLES, sample_level, ALLEGRO_SUGGEST);
	}
	else {
		al_set_new_display_option (ALLEGRO_SAMPLE_BUFFERS, 0, ALLEGRO_SUGGEST);
	}
	
	int hardware_acceleration = mConfig.getValue ( "video", "hardware_acceleration", util::Value ("1") ).getValue<int> ();
	al_set_new_display_option (ALLEGRO_RENDER_METHOD, hardware_acceleration, ALLEGRO_SUGGEST);

	bool page_flipping = mConfig.getValue ( "video", "page_flipping", util::Value ("0") ).getValue<bool> ();
	if (page_flipping) {
		al_set_new_display_option (ALLEGRO_SWAP_METHOD, 2, ALLEGRO_SUGGEST);
	}
	else {
		al_set_new_display_option (ALLEGRO_SWAP_METHOD, 1, ALLEGRO_SUGGEST);
	}

	int aux_buffers = mConfig.getValue ( "video", "aux_buffers", util::Value ("1") ).getValue<int> ();
	al_set_new_display_option (ALLEGRO_AUX_BUFFERS, aux_buffers, ALLEGRO_SUGGEST);

	bool vsync = mConfig.getValue ( "video", "vsync", util::Value ("0") ).getValue<bool> ();
	if (vsync) {
		al_set_new_display_option (ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	}
	else {
		al_set_new_display_option (ALLEGRO_VSYNC, 0, ALLEGRO_SUGGEST);
	}

	bool fullscreen = mConfig.getValue ( "video", "fullscreen", util::Value ("0") ).getValue<bool> ();
	if (fullscreen) {
		al_set_new_display_flags (ALLEGRO_FULLSCREEN);
	}
	else {
		al_set_new_display_flags (ALLEGRO_WINDOWED);
		bool resizable = mConfig.getValue ( "video", "resizable", util::Value ("1") ).getValue<bool> ();
		if (resizable) {
			al_set_new_display_flags (ALLEGRO_RESIZABLE);
		}
	}
	
	al_set_new_display_option (ALLEGRO_CAN_DRAW_INTO_BITMAP, 1, ALLEGRO_SUGGEST);
	al_set_new_display_flags (al_get_new_display_flags ());

	int width = mConfig.getValue ( "video", "width", util::Value ("1024") ).getValue<int> ();
	int height = mConfig.getValue ( "video", "height", util::Value ("768") ).getValue<int> ();
	// Creation of the display
	mDisplay = al_create_display (width, height);
	if (mDisplay == NULL) {
		std::stringstream ss;
		ss << al_get_errno ();
		throw lab::Exception (0, "io::Video.initialize error : Error during display creation (Errno " + ss.str () + ").");
	}

	// Setting display title
	al_set_window_title (mDisplay, mWindowName.c_str ());

	// Joining the display to the event queue
	registerAllegroEventSource (al_get_display_event_source (mDisplay));
}

void Video::shutdown () {
	unregisterAllegroEventSource (al_get_display_event_source (mDisplay));
	al_destroy_display (mDisplay);
	mDisplay = NULL;

	AllegroDevice::shutdown ();
}

void Video::handleInput () {
	// Notification des évenements aux listeners.
	ALLEGRO_EVENT event;
	while (getNextAllegroEvent (&event)) {
		if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
			event::Event e = event::Event (this, "video", "resize");
			e.addParameter ("width", util::Value (event.display.width));
			e.addParameter ("height", util::Value (event.display.height));
			notifyAll (e);
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			event::Event e = event::Event (this, "video", "close");
			notifyAll (e);
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN) {
			event::Event e = event::Event (this, "video", "switch_in");
			notifyAll (e);
		}
		else if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_OUT) {
			event::Event e = event::Event (this, "video", "switch_out");
			notifyAll (e);
		}
	}
}

void Video::cycle () {
	// Mise à jour de l'affichage.
	al_flip_display ();
	al_clear_to_color (al_map_rgb (0, 0, 0));
}

void Video::resize (int width, int height) {
	al_resize_display (mDisplay, width, height);
	al_acknowledge_resize (mDisplay);
}

}}
