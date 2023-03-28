/*
 * Cache.h
 * - Class to read from and write to a cache file
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

/*
 *  Class Cache is an interface to a cache file specified at construction.
 *  It is used to load cached data into and/or save data from a provided
 *  boost::json object. Load and save objects need not be identical.
 *
 *  If no cache file is specified at construction, a default in a location
 *  constructed from information provided in appdefaults.h is used.
 */

#ifndef SRC_CACHE_H_
#define SRC_CACHE_H_

#include <string>
#include <boost/json/object.hpp>
#include "appdefaults.h"
#include "Parser.h"	// defines namespace bjs

using std::string;

class Cache {
private:
	string			  cachefile;
	Parser			  parser;
	std::stringstream cache_ss;

	string makeCachefilePath(string appname, string cachefilename);

public:
	Cache(string cachefile);
	Cache();

	void load(bjs::object &obj);
	void save(bjs::object &obj);

	virtual ~Cache() {};
};

#endif /* SRC_CACHE_H_ */
