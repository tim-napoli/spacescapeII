#include <fstream>
#include <sstream>
#include <boost/regex.hpp>
#include "config/Configuration.hpp"

namespace lab {
namespace config {

Configuration::Configuration () : boost::unordered_map<std::string, Section> () {

}

Configuration::~Configuration () {

}

void Configuration::setValue (const std::string& section_name, const std::string& value_name, const util::Value& value) {
	auto got_sec = find (section_name);
	if (got_sec == end ()) {
		emplace (section_name, Section ());
		got_sec =find (section_name);
	}

	Section& section = got_sec->second;
	auto got_val = section.find (value_name);
	if (got_val != section.end ()) {
		got_val->second = value;
	}
	else {
		section.emplace (value_name, value);
	}
}

const util::Value& Configuration::getValue (const std::string& section_name, const std::string& value_name, 
									 		const util::Value& default_value) {
	auto got_sec = find (section_name);
	if (got_sec == end ()) {
		setValue (section_name, value_name, default_value);
		return getValue (section_name, value_name, default_value);
	}

	Section& section = got_sec->second;
	auto got_val = section.find (value_name);
	if (got_val == section.end ()) {
		section.emplace (value_name, default_value);
		return getValue (section_name, value_name, default_value);
	}

	return got_val->second;
}

void Configuration::merge (const Configuration& other) {
	for (auto it_s = other.begin (); it_s != other.end (); it_s++) {
		for (auto it_v = it_s->second.begin (); it_v != it_s->second.end (); it_v++) {
			setValue (it_s->first, it_v->first, it_v->second);
		}
	}
}

Configuration Configuration::extract (const std::string& section) {
	Configuration config = Configuration ();

	auto got = find (section);
	if (got != end ()) {
		for (auto it_v = got->second.begin (); it_v != got->second.end (); it_v++) {
			config.setValue (got->first, it_v->first, it_v->second);
		}
	}

	return config;
}

void Configuration::save (const std::string& path) const throw (lab::Exception) {
	std::ofstream file;

	file.open (path, std::fstream::out);
	if (!file.is_open ()) {
		throw lab::Exception (0, "Configuration::save error : Cannot write file " + path);
	}

	for (auto it_s = begin (); it_s != end (); it_s++) {
		file << "[" << it_s->first << "]\n";
		for (auto it_v = it_s->second.begin (); it_v != it_s->second.end (); it_v++) {
			file << it_v->first << " = \"" << it_v->second.getValue () << "\"\n";
		}
		file << "\n";
	}

	file.close ();
}

void Configuration::load (const std::string& path) throw (lab::Exception) {
	std::ifstream file;

	file.open (path, std::fstream::in);
	if (!file.is_open ()) {
		throw lab::Exception (0, std::string ("Configuration::load error : Cannot read file ") + path);
	}


	static const boost::regex reg_sec ("\\[([^\\]]+)\\]");
	static const boost::regex reg_val ("([_a-zA-Z0-9]+)[\\s]*=[\\s]*\"([^\"]+)\"");
	boost::cmatch result;
	std::string line;
	Section* section = NULL;
	int n = 1;

	while (!file.eof ()) {
		std::getline (file, line);

		if (!file.eof ()) {
			if (boost::regex_match (line.c_str (), result, reg_sec)) {
				emplace (result [1], boost::unordered_map<std::string, util::Value> ());
				section = &(find (result [1])->second);
			}
			else if (boost::regex_match (line.c_str (), result, reg_val)) {
				if (section == NULL) {
					file.close ();
					std::stringstream ss;
					ss << "Configuration::load error : Orpheline value (line " << n << ").";
					throw lab::Exception (1, ss.str ());
				}
				section->emplace (result [1], util::Value (result [2]));
			}
			else if (line.compare ("") == 0) {
				section = NULL;
			}
			else {
				file.close ();
				std::stringstream ss;
				ss << "Configuration::load error : Invalide line (line " << n << ").";
				throw lab::Exception (2, ss.str ());
			}
		}

		n++;
	}

	file.close ();
}

}}

