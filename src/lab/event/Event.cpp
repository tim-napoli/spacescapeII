#include "event/Event.hpp"

namespace lab {
namespace event {

void Event::addParameter (const std::string& name, const util::Value& value) throw (lab::Exception) {
	boost::unordered_map<std::string, util::Value>::iterator got = mParams.find (name);
	if (got != mParams.end ()) {
		std::string msg = "Event.addParameter error : Parameter " + name + " already exists !";
		throw lab::Exception (0, msg);
	}

	mParams.emplace (name, value);
}

Event::Event (const Generator* generator, const std::string& type, const std::string& subtype) {
	mGenerator = generator;
	mType = type;
	mSubType = subtype;
	mParams = boost::unordered_map<std::string, util::Value> ();
}

Event::~Event () {
	mParams.clear ();
}

const util::Value& Event::getParameter (const std::string& name) const throw (lab::Exception) {
	boost::unordered_map<std::string, util::Value>::const_iterator got = mParams.find (name);
	if (got == mParams.end ()) {
		std::string msg = "Event.addParameter error : Parameter " + name + " does not exist !";
		throw lab::Exception (0, msg);
	}

	return got->second;
}

}}

