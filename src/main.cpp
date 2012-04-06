/*
 * SymlinkMerge.cpp
 *
 * Author: Shadab Ansari
 */

#include <iostream>
#include "merge.h"
#include "options.h"

using namespace SymlinkMerge;

int main(int argc, char** argv) {

	options opt(argc, argv);

	if (opt.count("help")) {
		std::cout << opt.description();
		return 0;
	}

	if (opt.count("interactive")) {
		opt.process_config_interactive(std::cin, std::cout);
	}

	std::string target = opt.target_path();
	std::vector<std::string> sources = opt.source_paths();

	if (target.empty() || sources.empty()) {
		std::cerr << "Source or Target path not specified." << std::endl;
		return 1;
	}

	merge _m(&std::cout, &std::cerr);
	_m.create_symlinks(sources, target, opt.base_path());

	return 0;
}
