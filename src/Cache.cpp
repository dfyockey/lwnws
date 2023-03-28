/*
 * Cache.cpp
 * - Class Cache method implementations
 *
 * Copyright 2022,2023 David Yockey
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
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

Cache::Cache(string cachefile) : cachefile(cachefile) {};

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
