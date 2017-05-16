#include <string>
#include <allegro5/allegro.h>

#include "io/Keyboard.hpp"

#include "util/Value.hpp"

namespace lab {
namespace io {

Keyboard::Keyboard () : AllegroDevice ("Keyboard") {
	
}

Keyboard::~Keyboard () {

}

void Keyboard::initialize () throw (Exception) {
	AllegroDevice::initialize ();

	if (!al_install_keyboard ()) {
		throw Exception (0, "Keyboard.initialize error : Error during the keyboard installation.");
	}

	// Joining the keyboard to the event queue
	registerAllegroEventSource (al_get_keyboard_event_source ());
}

void Keyboard::shutdown () {
	unregisterAllegroEventSource (al_get_keyboard_event_source ());
	al_uninstall_keyboard ();

	AllegroDevice::shutdown ();
}

void Keyboard::handleInput () {
	ALLEGRO_EVENT event;
	while (getNextAllegroEvent (&event)) {
		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			event::Event e = event::Event (this, "keyboard", "key_down");
			e.addParameter ("keycode", util::Value (event.keyboard.keycode));
			notifyAll (e);
 		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			event::Event e = event::Event (this, "keyboard", "key_up");
			e.addParameter ("keycode", util::Value (event.keyboard.keycode));
			notifyAll (e);
		}
		else if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
			event::Event e = event::Event (this, "keyboard", "key_char");
			e.addParameter ("keycode", 		util::Value (event.keyboard.keycode));
			e.addParameter ("unichar", 		util::Value (event.keyboard.unichar));
			e.addParameter ("modifiers", 	util::Value (event.keyboard.modifiers));
			e.addParameter ("repeat", 		util::Value (event.keyboard.repeat));
			notifyAll (e);
		}
	}
}

void Keyboard::cycle () {

}

}}

