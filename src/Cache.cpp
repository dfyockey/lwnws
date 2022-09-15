/*
 * Cache.cpp
 *
 *  Created on: Sep 7, 2022
 *      Author: David
 */

#include "Cache.h"

#include <filesystem>
#include <fstream>
#include <boost/json/serialize.hpp>

std::string cachefile = "/home/David/Projects/Workspace_C++/lwnws/Debug/lwnws_cache";

///// private: ///////////////////////////////////////////////////////

void Cache::loadcache() {
	std::ifstream fcache(cachefile);
	if (fcache)
		cached_parsed_weather_ss << fcache.rdbuf();
}

void Cache::reconcile() {

}

///// public: ////////////////////////////////////////////////////////

Cache::Cache(boost::json::value parsed_weather) : parsed_weather(parsed_weather.as_object()) {
	namespace fs = std::filesystem;

	fs::path f(cachefile.c_str());
	if (!fs::exists(f)) {
		std::string pw = serialize(parsed_weather);
		std::ofstream fcache(cachefile);
		if (fcache)
			fcache << pw;
		cached_parsed_weather_ss << pw;
	} else {
		loadcache();
	}
}

std::string Cache::dump() {	return cached_parsed_weather_ss.str(); }

Cache::~Cache() {
	// TODO Auto-generated destructor stub
}

