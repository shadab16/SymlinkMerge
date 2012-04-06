/*
 * invalid_path.cpp
 *
 * Author: Shadab Ansari
 */

#include "invalid_path.h"

namespace SymlinkMerge {

	invalid_path::invalid_path(fs::path path) throw() : _path(path) {
		;
	}

	const fs::path invalid_path::path() const throw() {
		return this->_path;
	}

	const char* invalid_path::what() const throw() {
		return "Supplied path is not a valid directory.";
	}

	invalid_path::~invalid_path() throw() {
		;
	}
}
