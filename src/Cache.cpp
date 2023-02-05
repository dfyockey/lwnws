/*
 * Cache.cpp
 *
 *  Created on: Sep 7, 2022
 *      Author: David Yockey
 */

#include "Cache.h"

#include <filesystem>
#include <fstream>
#include <utility>
#include <iostream>
#include <boost/json/serialize.hpp>

namespace fsys = std::filesystem;

///// private: ///////////////////////////////////////////////////////

string Cache::makeCachefilePath(string appname, string cachefilename) {
	// Returns the default cachefile path `$HOME/.<appname>/<cachefilename>`,
	// where $HOME is the value of the HOME environment variable.

	string HOME(getenv("HOME"));
	return HOME + "/." + appname + "/" + cachefilename;
}

///// public: ////////////////////////////////////////////////////////
Cache::Cache() {
	cachefile = makeCachefilePath(appdefs::APPNAME, appdefs::CACHENAME);
}

void Cache::load (bjs::object &obj) {
	/*
	 * If file does not exist or ifstream construction fails for some reason,
	 * the referenced value will be unchanged.
	 */
	try {
		fsys::path f(cachefile.c_str());
		if (fsys::exists(f)) {
			std::ifstream fcache(cachefile);
			if (fcache) {
				cache_ss << fcache.rdbuf();
				obj = parser.parse(cache_ss.str()).as_object();
			}
		}
	} catch (fsys::filesystem_error& e) {
		std::cerr << "Load from " << cachefile << " failed: " << e.what();
	}
}

void Cache::save (bjs::object &obj) {
	string s = serialize(obj);

	std::ofstream fcache(cachefile, std::ios::out|std::ios::trunc);
	if(fcache)
		fcache.write(s.c_str(), s.length());
	else
		std::cerr << "Open file " << cachefile << " for save failed\n";
}
