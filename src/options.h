/*
 * options.h
 *
 * Author: Shadab Ansari
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <istream>
#include <ostream>
#include <fstream>
#include <string>

#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

namespace SymlinkMerge {

	namespace po = boost::program_options;
	namespace fs = boost::filesystem;

	class options {
	protected:
		po::options_description _description;
		po::variables_map _map;

		// Option values
		std::string _config_path;
		std::string _target_path;
		std::vector<std::string> _source_paths;
	public:
		options(int, char**) throw();

		po::options_description description() throw();
		po::variables_map::size_type count(std::string) throw();

		std::string base_path() throw();
		std::string config_path() throw();
		std::string target_path() throw();
		std::vector<std::string> source_paths() throw();

		void process_config_ini(std::string) throw();
		void process_config_interactive(std::istream&, std::ostream&) throw();
	};
}

#endif /* OPTIONS_H_ */
