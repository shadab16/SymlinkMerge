/*
 * symlink_exists.h
 *
 * Author: Shadab Ansari
 */

#ifndef SYMLINK_EXISTS_H_
#define SYMLINK_EXISTS_H_

#include <exception>
#include <map>
#include "boost/filesystem.hpp"

namespace SymlinkMerge {

	namespace fs = boost::filesystem;

	class symlink_exists : public std::exception {
	protected:
		const std::map<fs::path, fs::path> _conflicts;
	public:
		symlink_exists(std::map<fs::path, fs::path>) throw();
		const std::map<fs::path, fs::path> conflicts() const throw();
		virtual const char* what() const throw();
		virtual ~symlink_exists() throw();
	};
}

#endif /* SYMLINK_EXISTS_H_ */
