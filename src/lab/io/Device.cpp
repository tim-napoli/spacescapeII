#include <string>

#include <allegro5/allegro.h>
#include "event/Generator.hpp"
#include "io/Device.hpp"

namespace lab {
namespace io {

Device::Device (const std::string& name) : Generator () {
	mName = name;
}

Device::~Device () {

}

}}

