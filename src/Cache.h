/*
 * Cache.h
 *
 *  Created on: Sep 7, 2022
 *      Author: David Yockey
 *
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
