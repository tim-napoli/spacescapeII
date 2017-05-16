#include "activity/Activity.hpp"

namespace lab {
namespace activity {

Activity::Activity (Engine* engine) {
	mEngine = engine;

	mBinder = Binder ();
	mRenderer = NULL;

	mInitialized = false;
}

Activity::~Activity () {

}

void Activity::initialize () throw (lab::Exception) {
	mInitialized = true;
}

void Activity::shutdown () {
	mInitialized = false;
}

void Activity::notify (const event::Event& event) {
	mBinder.notify (event);
}

}}

