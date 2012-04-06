/*
 * merge.h
 *
 * Author: Shadab Ansari
 */

#ifndef MERGE_H_
#define MERGE_H_

#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "invalid_path.h"
#include "symlink_exists.h"

#include "boost/filesystem.hpp"

namespace SymlinkMerge {

	namespace fs = boost::filesystem;

	class merge {
	protected:
		std::auto_ptr<std::map<fs::path, fs::path> > _directory_symlinks;

		std::ostream* _out;
		std::ostream* _err;

		void _symlink_tree(fs::path, fs::path) throw(invalid_path, symlink_exists);
		void _merge_tree(fs::path, fs::path) throw();
		void _merge_all_trees(std::vector<fs::path>, fs::path) throw();
	public:
		merge() throw();
		merge(std::ostream*, std::ostream*) throw();
		~merge() throw();

		void create_symlinks(std::vector<std::string>, std::string, std::string) throw();
		void create_symlinks(std::vector<std::string>, std::string) throw();
	};
}

#endif /* MERGE_H_ */
