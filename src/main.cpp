/*
 * main.cpp
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

#define BOOST_LOG_DYN_LINK 1

#include <iostream>
#include <string>
#include <exception>

#include <boost/json/src.hpp>
#include <boost/program_options.hpp>
#include <curl/curl.h>

#include "NWSDataRetriever.h"
#include "NWSDataCombiner.h"
#include "DisplayFormatter.h"
#include "Cache.h"

#include <boost/json/object.hpp>
#include <boost/json/value.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>		// need for `boost::log::add_file_log`
#include <boost/log/sources/logger.hpp>			// need for `boost::log::sources::logger`
#include <boost/log/utility/setup/common_attributes.hpp>

#include "util/filesysutil.hpp"

namespace dfo = DisplayFormatter;

// logging sink
namespace logging  = boost::log;
namespace keywords = boost::log::keywords;

// logging source
namespace src      = boost::log::sources;

using std::cout;
using std::endl;
using std::string;
using std::to_string;

///// Initialization of Program Options //////////////////////////////

namespace bop = boost::program_options;

bop::options_description initDescription() {

	bop::options_description desc("\nDetermines and outputs the latest weather conditions at the\n"
			                        "U.S. National Weather Service observation station closest to\n"
			                        "the specified location based on publicly available NWS data.\n"
			                      "\n  Command Line Options");

	desc.add_options()
		( "help,h", "Generate help message." )
		( "json,j", "Return JSON data for current weather at specified location, modified by cached data as needed." )
		( "rawjson,r", "Return JSON data for current weather at specified location, unmodified (i.e. direct from NWS API)." )
		( "lat", bop::value<float>()->default_value( 38.99322, " 38.99322"), "Latitude" )
		( "lon", bop::value<float>()->default_value(-77.03207, "-77.03207"), "Longitude" )
	;

	return desc;
}

bop::variables_map initVariablesMap(int argc, char* argv[], bop::options_description& desc) {
	bop::variables_map vm;
	bop::store(bop::parse_command_line(argc, argv, desc), vm);
	bop::notify(vm);
	return vm;
}

///// Logging ////////////////////////////////////////////////////////

void initlog()
{
	const std::ios_base::openmode APPEND2LOG = std::ios_base::out|std::ios_base::app;

	logging::add_file_log(
		keywords::file_name  =  filesysutil::homedir() + "/.lwnws/lwnws.log",
		keywords::open_mode  =  APPEND2LOG,
		keywords::auto_flush =  true,
		keywords::format	 = "%TimeStamp% — %Message%"
	);

	logging::add_common_attributes();
}

///// Actual Program /////////////////////////////////////////////////

string getCombinedWeather(NWSDataRetriever& nwsDataRetriever, bool display) {
	Cache cache;

	Weather lw = nwsDataRetriever.getLocalWeather();
	Weather cw = nwsDataRetriever.getCacheWeather(cache);
	NWSDataCombiner::combine(lw, cw);

	string weather = (display) ? DisplayFormatter::formatWeather(lw) : serialize(lw);

	// Save to cache last so any new data that causes an exception throw won't be saved.
	cache.save(lw);

	return weather;
}

void _execMain(bop::variables_map& vm) {
	const bool DISPLAY = true;
	const bool JSON    = false;

	NWSDataRetriever nwsDataRetriever( vm["lat"].as<float>(), vm["lon"].as<float>() );

	if (vm.count("json"))
		cout << getCombinedWeather(nwsDataRetriever, JSON) << endl;
	else if (vm.count("rawjson"))
		cout << nwsDataRetriever.getLocalWeatherJSON() << endl;
	else
		cout << getCombinedWeather(nwsDataRetriever, DISPLAY) << std::flush;  // no endl facilitates use in Conky display
}

int execMain(bop::variables_map& vm) {
	try {
		_execMain(vm);
	} catch (std::runtime_error& e) {
		src::logger lg;
		BOOST_LOG(lg) << "Runtime Error : " << e.what();
		return -1;
	} catch (std::exception &e) {
		src::logger lg;
		BOOST_LOG(lg) << "Unknown Error : " << e.what();
		return -2;
	}
	return 0;
}

int main(int argc, char* argv[]) {

	initlog();

	bop::options_description desc = initDescription();
	bop::variables_map vm = initVariablesMap(argc, argv, desc);

	if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}

	return execMain(vm);
}
