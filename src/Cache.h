/*
 * Cache.h
 *
 *  Created on: Sep 7, 2022
 *      Author: David Yockey
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
	Cache(string cachefile) : cachefile(cachefile) {};
	Cache();

	void load(bjs::object &obj);
	void save(bjs::object &obj);

	virtual ~Cache() {};
};

#endif /* SRC_CACHE_H_ */
