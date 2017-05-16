#include <exception>
#include <string>
#include "Exception.hpp"

namespace lab {

Exception::Exception (int code, const std::string& message) throw () {
	mCode = code;
	mMessage = message;
}

Exception::~Exception () throw () {

}

const char* Exception::what () const throw () {
	return mMessage.c_str ();
}

}
