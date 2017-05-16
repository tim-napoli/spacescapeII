#include "config/Configurable.hpp"

namespace lab {
namespace config {

Configurable::Configurable () {
	mConfig = Configuration ();
}

Configurable::~Configurable () {
	mConfig.clear ();
}

}}

