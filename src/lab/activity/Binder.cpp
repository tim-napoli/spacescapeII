#include "Exception.hpp"
#include "activity/Binder.hpp"

namespace lab {
namespace activity {

EventChecker::~EventChecker () {

}

/******************************************************* Bind *********************************************************/
Bind::Bind (EventChecker* checker, Task* task, bool temporary) {
	mChecker = checker;
	mTask = task;
	mTemporary = temporary;
}

Bind::~Bind () {
	delete mChecker;
	delete mTask;
}

void Bind::execute (const event::Event& event) {
	mTask->execute (event);
}

bool Bind::check (const event::Event& event) {
	return mChecker->check (event);
}

/****************************************************** Binder ********************************************************/
Binder::Binder () {
	mEventMap = boost::unordered_map<std::string, boost::unordered_map<std::string, std::list<Bind*>>> ();
}

Binder::~Binder () {
	clearBinds ();
}

void Binder::addBind (const std::string& event_type, const std::string& event_subtype, Bind* bind) {
	auto got_t = mEventMap.find (event_type);
	if (got_t == mEventMap.end ()) {
		mEventMap.emplace (event_type, boost::unordered_map<std::string, std::list<Bind*>> ());
		got_t = mEventMap.find (event_type);
	}

	boost::unordered_map<std::string, std::list<Bind*>>& subtype_map = got_t->second;
	auto got_st = subtype_map.find (event_subtype);
	if (got_st == subtype_map.end ()) {
		subtype_map.emplace (event_subtype, std::list<Bind*> ());
		got_st = subtype_map.find (event_subtype);
	}

	got_st->second.push_back (bind);
}

void Binder::notify (const event::Event& event) {
	// Looking in the type map.
	auto got_type = mEventMap.find (event.getType ());
	if (got_type != mEventMap.end ()) {
		// Looking in the subtype map.
		auto got_subtype = got_type->second.find (event.getSubType ());
		if (got_subtype != got_type->second.end ()) {
			// Check if a bind is corresponding to this event.
			for (auto it = got_subtype->second.begin (); it != got_subtype->second.end (); it++) {
				if ((*it)->check (event)) {
					(*it)->execute (event);
					
					// If the bind is temporary, it must be destroyed after usage.
					if ((*it)->isTemporary ()) {
						delete *it;
						it = got_subtype->second.erase (it);
						it--;
					}
				}
			}
		}
	}
}

void Binder::clearBinds () {
	for (auto it_t = mEventMap.begin (); it_t != mEventMap.end (); it_t++) {
		for (auto it_st = it_t->second.begin (); it_st != it_t->second.end (); it_st++) {
			for (auto it_b = it_st->second.begin (); it_b != it_st->second.end (); it_b++) {
				delete *it_b;
			}
			it_st->second.clear ();
		}
		it_t->second.clear ();
	}
	mEventMap.clear ();
}

void Binder::clearTemporaries () {
	for (auto it_t = mEventMap.begin (); it_t != mEventMap.end (); it_t++) {
		for (auto it_st = it_t->second.begin (); it_st != it_t->second.end (); it_st++) {
			for (auto it_b = it_st->second.begin (); it_b != it_st->second.end (); it_b++) {
				if ((*it_b)->isTemporary ()) {
					delete *it_b;
					it_b = it_st->second.erase (it_b);
					it_b--;
				}
			}
		}
	}
}

void Binder::clearBind (Bind* addr) {
	for (auto it_t = mEventMap.begin (); it_t != mEventMap.end (); it_t++) {
		for (auto it_st = it_t->second.begin (); it_st != it_t->second.end (); it_st++) {
			for (auto it_b = it_st->second.begin (); it_b != it_st->second.end (); it_b++) {
				if ((*it_b) == addr) {
					delete *it_b;
					it_b = it_st->second.erase (it_b);
					it_b--;
				}
			}
		}
	}
}

/*************************************************** EventCheckers ****************************************************/
KeyEventChecker::KeyEventChecker (int keycode) {
	mKeycode = keycode;
}

KeyEventChecker::~KeyEventChecker () {

}

bool KeyEventChecker::check (const event::Event& event) const {
	try {
		util::Value val = event.getParameter ("keycode");
		return val.getValue<int> () == mKeycode;
	} catch (const lab::Exception& e) {
		return false;
	}
}

EverEventChecker::EverEventChecker () {

}

EverEventChecker::~EverEventChecker () {

}

bool EverEventChecker::check (const event::Event& event) const {
	(void) event;

	return true;
}

}}

