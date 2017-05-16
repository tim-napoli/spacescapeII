#ifndef _lab_config_Configurable_hpp_
#define _lab_config_Configurable_hpp_

#include "lab/config/Configuration.hpp"

namespace lab {
namespace config {

class Configurable {
	protected:
		Configuration	mConfig;

	public:
		Configurable ();

		~Configurable ();

		void setConfiguration (const Configuration& config) {mConfig = config;};

		const Configuration& getConfiguration () const {return mConfig;}
};

}}

#endif

