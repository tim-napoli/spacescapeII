#include "lab/io/Mouse.hpp"

using namespace lab::io;

namespace lab {
namespace io {

Mouse::Mouse () : AllegroDevice ("Mouse") {
	
}

Mouse::~Mouse () {

}

void Mouse::initialize () throw (lab::Exception) {
	AllegroDevice::initialize ();
	
	if (!al_install_mouse ()) {
		throw lab::Exception (0, "Mouse::initialize Error : Allegro cannot install the mouse !");
	}
	
	registerAllegroEventSource (al_get_mouse_event_source ());
}

void Mouse::shutdown () {
	unregisterAllegroEventSource (al_get_mouse_event_source ());
	al_uninstall_mouse ();
	
	AllegroDevice::shutdown ();
}

void Mouse::handleInput () {
	ALLEGRO_EVENT event;
	while (getNextAllegroEvent (&event)) {
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			event::Event e = event::Event (this, "mouse", "move");
			e.addParameter ("x", util::Value (event.mouse.x));
			e.addParameter ("y", util::Value (event.mouse.y));
			e.addParameter ("z", util::Value (event.mouse.z));
			e.addParameter ("dx", util::Value (event.mouse.dx));
			e.addParameter ("dy", util::Value (event.mouse.dy));
			e.addParameter ("dz", util::Value (event.mouse.dz));
			notifyAll (e);
 		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			event::Event e = event::Event (this, "mouse", "down");
			e.addParameter ("x", util::Value (event.mouse.x));
			e.addParameter ("y", util::Value (event.mouse.y));
			e.addParameter ("z", util::Value (event.mouse.z));
			e.addParameter ("button", util::Value (event.mouse.button));
			notifyAll (e);
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			event::Event e = event::Event (this, "mouse", "up");
			e.addParameter ("x", util::Value (event.mouse.x));
			e.addParameter ("y", util::Value (event.mouse.y));
			e.addParameter ("z", util::Value (event.mouse.z));
			e.addParameter ("button", util::Value (event.mouse.button));
			notifyAll (e);
		}
	}
}

void Mouse::cycle () {

}

}}
