/*
 * options.cpp
 *
 * Author: Shadab Ansari
 */

#include "options.h"

namespace SymlinkMerge {

	options::options(int argc, char** argv) throw() : _description("Options Available") {

		_description.add_options()
				("help", "Display this help message")
				("interactive,I", "Run this program interactively")
				("config", po::value<std::string>(&_config_path)->default_value("config.ini"), "Path to configuration file")
		;

		po::store(po::parse_command_line(argc, argv, _description), _map);
		po::notify(_map);

		process_config_ini(_config_path);
	}

	po::options_description options::description() throw() {
		return _description;
	}

	po::variables_map::size_type options::count(std::string key) throw() {
		return _map.count(key);
	}

	std::string options::base_path() throw() {

		fs::path path(_config_path);
		return fs::system_complete(path).parent_path().string();
	}

	std::string options::config_path() throw() {
		return _config_path;
	}

	std::string options::target_path() throw() {
		return _target_path;
	}

	std::vector<std::string> options::source_paths() throw() {
		return _source_paths;
	}

	void options::process_config_ini(std::string path) throw() {

		po::options_description description;
		po::variables_map map;

		description.add_options()
				("target", po::value<std::string>(&_target_path))
				("sources[]", po::value<std::vector<std::string> >(&_source_paths))
		;

		std::ifstream file(path.c_str());
		po::store(po::parse_config_file(file, description), map);
		po::notify(map);
	}

	void options::process_config_interactive(std::istream& in, std::ostream& out) throw() {

		_source_paths.clear();

		out << "Target Path:" << std::endl;
		std::getline(in, _target_path);

		in.clear();

		std::string source_path = "";
		out << "Source Paths:" << std::endl;

		while (1) {
			std::getline(in, source_path);
			if (!source_path.length()) {
				break;
			}
			_source_paths.push_back(source_path);
		}
	}
}
