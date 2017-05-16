#include <allegro5/allegro.h>
#include "Exception.hpp"
#include "io/Device.hpp"
#include "io/AllegroDevice.hpp"

namespace lab {
namespace io {

AllegroDevice::AllegroDevice (const std::string& name) : Device (name) {
	mEvents = NULL;
}

AllegroDevice::~AllegroDevice () {

}

void AllegroDevice::registerAllegroEventSource (ALLEGRO_EVENT_SOURCE* source) {
	al_register_event_source (mEvents, source);
}

void AllegroDevice::unregisterAllegroEventSource (ALLEGRO_EVENT_SOURCE* source) {
	al_unregister_event_source (mEvents, source);
}

bool AllegroDevice::getNextAllegroEvent (ALLEGRO_EVENT* e) {
	return (bool) al_get_next_event (mEvents, e);
}

void AllegroDevice::initialize () throw (lab::Exception) {
	mEvents = al_create_event_queue ();
}

void AllegroDevice::shutdown () {
	al_destroy_event_queue (mEvents);
	mEvents = NULL;
}

}}

