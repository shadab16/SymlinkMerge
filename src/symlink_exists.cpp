/*
 * symlink_exists.cpp
 *
 * Author: Shadab Ansari
 */

#include "symlink_exists.h"

namespace SymlinkMerge {

	symlink_exists::symlink_exists(std::map<fs::path, fs::path> conflicts) throw() : _conflicts(conflicts) {
		;
	}

	const std::map<fs::path, fs::path> symlink_exists::conflicts() const throw() {
		return this->_conflicts;
	}

	const char* symlink_exists::what() const throw() {
		return "Cannot create symlink to the source directory. "
		       "A symlink by the same name already exists.";
	}

	symlink_exists::~symlink_exists() throw() {
		;
	}
}
