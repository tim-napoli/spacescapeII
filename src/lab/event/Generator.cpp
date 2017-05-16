#include "Exception.hpp"
#include "event/Event.hpp"
#include "event/Listener.hpp"
#include "event/Generator.hpp"
#include <iostream>

namespace lab {
namespace event {

Generator::Generator () {
	mListeners = std::list<Listener*> ();
}

Generator::~Generator () {
	mListeners.clear ();
}

bool Generator::isListenerRegistred (const Listener* listener) const {
	for (std::list<Listener*>::const_iterator it = mListeners.begin (); it != mListeners.end (); it++) {
		if (*it == listener) {
			return true;
		}
	}

	return false;
}

void Generator::registerListener (Listener* listener) throw (lab::Exception) {
	if (isListenerRegistred (listener)) {
		throw lab::Exception (0, "Generator::registerListener error : submited listener is already registred.");
	}

	mListeners.push_back (listener);
}

void Generator::unregisterListener (Listener* listener) throw (lab::Exception) {
	if (!isListenerRegistred (listener)) {
		throw lab::Exception (0, "Generator::unregisterListener error : submited listener is not registred.");
	}

	for (std::list<Listener*>::iterator it = mListeners.begin (); it != mListeners.end (); it++) {
		if (*it == listener) {
			mListeners.erase (it);
			break;
		}
	}
}

void Generator::notifyAll (const Event& event) {
	for (std::list<Listener*>::iterator it = mListeners.begin (); it != mListeners.end (); it++) {
		(*it)->notify (event);
	}
}

}}

