/*
 * merge.cpp
 *
 * Author: Shadab Ansari
 */

#include "merge.h"

namespace SymlinkMerge {

	merge::merge() throw()
			: _directory_symlinks(new std::map<fs::path, fs::path>), _out(0), _err(0) {
		;
	}

	merge::merge(std::ostream* out, std::ostream* err) throw()
			: _directory_symlinks(new std::map<fs::path, fs::path>), _out(out), _err(err) {
		;
	}

	merge::~merge() throw() {
		;
	}

	void merge::_symlink_tree(fs::path source, fs::path target) throw(symlink_exists, invalid_path) {

		if (!fs::is_directory(source)) {
			throw invalid_path(source);
		}

		if (!fs::is_directory(target)) {
			throw invalid_path(target);
		}

		if (fs::equivalent(source, target)) {
			// Lookup map for directory symlinks
			if (fs::is_directory(source)) {
				(*_directory_symlinks)[target] = source;
			}
			return; // Better error handling? Throw an exception?
		}

		std::map<fs::path, fs::path> relink;

		for (fs::directory_iterator iter(source), end; iter != end; ++iter) {

			fs::path source_node(*iter);
			fs::path target_node = target / source_node.filename();

			if (source_node.filename().at(0) == '.') {
				// Ignore files and directory names starting with a "."
				continue;
			}

			if (fs::is_symlink(target_node)) {
				if (!fs::equivalent(source_node, target_node)) {
					relink[source_node] = target_node;
				}
			} else if (fs::is_directory(target_node) && fs::is_directory(source_node)) {
				_symlink_tree(source_node, target_node);
			} else if (!fs::exists(target_node)) {
				fs::create_symlink(source_node, target_node);
			}

			// Lookup map for directory symlinks
			if (fs::equivalent(source_node, target_node) && fs::is_directory(source_node)) {
				(*_directory_symlinks)[target_node] = source_node;
			}
		}

		if (relink.size() > 0) {
			throw symlink_exists(relink);
		}
	}

	void merge::_merge_tree(fs::path source, fs::path target) throw() {

		std::map<fs::path, fs::path> relink;
		std::vector<fs::path> fixed;

		try {
			_symlink_tree(source, target);
		} catch (symlink_exists& e) {
			relink = e.conflicts();
		} catch (invalid_path& e) {
			if (_err) {
				(*_err) << e.what() << "\n" << e.path() << std::endl;
			}
		}

		std::map<fs::path, fs::path>::iterator iter;
		for (iter = relink.begin(); iter != relink.end(); ++iter) {

			fs::path target_node = (*iter).second;
			fs::path relink_node = (*iter).first;
			fs::path original_node = (*_directory_symlinks)[target_node];

			fs::remove(target_node);
			fs::create_directory(target_node);

			_merge_tree(original_node, target_node);
			_merge_tree(relink_node, target_node);
		}
	}

	void merge::_merge_all_trees(std::vector<fs::path> sources, fs::path target) throw() {

		std::vector<fs::path>::iterator iter;
		for (iter = sources.begin(); iter != sources.end(); ++iter) {
			_merge_tree(*iter, target);
		}
	}

	void merge::create_symlinks(std::vector<std::string> sources, std::string target, std::string base) throw() {

		std::vector<fs::path> paths;
		std::vector<std::string>::iterator iter;

		for (iter = sources.begin(); iter != sources.end(); ++iter) {
			fs::path path(*iter);
			if (path.root_path().empty() && !base.empty()) {
				path = base / path;
			}
			paths.push_back(fs::system_complete(path));
		}
		_merge_all_trees(paths, fs::system_complete(target));
	}

	void merge::create_symlinks(std::vector<std::string> sources, std::string target) throw() {

		std::string base = "";
		create_symlinks(sources, target, base);
	}
}
