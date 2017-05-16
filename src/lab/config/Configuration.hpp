#ifndef _lab_config_Configuration_hpp_
#define _lab_config_Configuration_hpp_

#include <string>
#include <boost/unordered_map.hpp>

#include "lab/Exception.hpp"
#include "lab/util/Value.hpp"

namespace lab {
/*!
 * \brief The configuration's related classes.
 */
namespace config {

typedef boost::unordered_map<std::string, util::Value> Section;

/*!
 * \brief A Configuration is a data structure that will groups values, with the intention to save and load them on a persistent
 * 		  memory.
 */
class Configuration : public boost::unordered_map<std::string, Section> {
	public:
		/*!
		 * \brief Constructor.
		 */
		Configuration ();

		/*!
		 * \brief Destructor.
		 */
		~Configuration ();

		/*!
		 * \brief Set a value to the configuration. Will create the section if it isn't exist.
		 * \param section_name The Section's name.
		 * \param value_name The Value's name.
		 * \param value The value to add.
		 */
		void setValue (const std::string& section_name, const std::string& value_name, const util::Value& value);

		/*!
		 * \brief Get a value of the configuration. If it isn't exist, it will be created with the default value passed
		 *		  as argument.
		 * \param section_name The Section's name.
		 * \param value_name The Value's name.
		 * \param default_value The default value of the Value if this Value isn't exist.
		 * \return The value of the value.
		 */
		const util::Value& getValue (const std::string& section_name, const std::string& value_name, 
									 const util::Value& default_value);

		/*!
		 * \brief Merge two configurations. All values of the parameters config will be copied in this one. If a parmater
		 *		  exist in the two configs, this of the other will be used.
		 * \param other The other Configuration.
		 */
		void merge (const Configuration& other);

		/*!
		 * \brief Extract a section from this configuration, and create a new config with.
		 * \param section The name of the section to extract.
		 */
		Configuration extract (const std::string& section); // TODO: adding a throw of exception.

		/*!
		 * \brief Save the Configuration on the Hard Drive.
		 * \param path The path where to save the configuration file.
		 * \throw lab::Exception if an error occured.
		 */
		void save (const std::string& path) const throw (lab::Exception);

		/*!
		 * \brief Load a Configuration from the Hard Drive.
		 * \param path The path of the file.
		 * \throw lab::Exception if an error occured.
		 */
		void load (const std::string& path) throw (lab::Exception);
		
		/*!
		 * \brief operator =.
		 */
		Configuration& operator = (const Configuration& other) {merge (other); return *this;}
};

}}

#endif

