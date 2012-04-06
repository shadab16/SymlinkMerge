/*
 * invalid_path.h
 *
 * Author: Shadab Ansari
 */

#ifndef INVALID_PATH_H_
#define INVALID_PATH_H_

#include <exception>
#include "boost/filesystem.hpp"

namespace SymlinkMerge {

	namespace fs = boost::filesystem;

	class invalid_path : public std::exception {
	protected:
		const fs::path _path;
	public:
		invalid_path(fs::path) throw();
		const fs::path path() const throw();
		virtual const char* what() const throw();
		virtual ~invalid_path() throw();
	};
}

#endif /* INVALID_PATH_H_ */
