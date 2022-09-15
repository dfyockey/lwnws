/*
 * Cache.h
 *
 *  Created on: Sep 7, 2022
 *      Author: David
 */

#ifndef SRC_CACHE_H_
#define SRC_CACHE_H_

#include <string>
#include <boost/json/object.hpp>

class Cache {
private:
	std::stringstream	cached_parsed_weather_ss;
	boost::json::object cached_parsed_weather;
	boost::json::object parsed_weather;

	void loadcache();
	void reconcile();

public:
	Cache(boost::json::value parsed_weather);

	std::string dump();

	virtual ~Cache();
};

#endif /* SRC_CACHE_H_ */
