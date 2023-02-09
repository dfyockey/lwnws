/*
 * main.cpp
 *
 *  Created on: Jul 31, 2022
 *      Author: David Yockey
 */

#include <iostream>

#include <boost/json/src.hpp>
#include <boost/program_options.hpp>
#include <curl/curl.h>

#include "NWSDataRetriever.h"
#include "NWSDataCombiner.h"
#include "DisplayFormatter.h"
#include "Cache.h"

#include <boost/json/object.hpp>
#include <boost/json/value.hpp>

namespace bop = boost::program_options;
namespace dfo = DisplayFormatter;

using std::cout;
using std::endl;
using std::to_string;

///// Initialization of Program Options //////////////////////////////
bop::options_description initDescription() {

	bop::options_description desc("\nGets the latest weather conditions at the U.S. National Weather Service\n"
			                      "observation station closest to the specified location.\n\n  Command Line Options");

	desc.add_options()
		( "help,h", " generate help message" )
		( "json,j", " return unparsed JSON data for the specified location" )
		( "lat", bop::value<float>()->default_value( 38.99322, " 38.99322"), " latitude" )
		( "lon", bop::value<float>()->default_value(-77.03207, "-77.03207"), " longitude" )
	;

	return desc;
}

bop::variables_map initVariablesMap(int argc, char* argv[], bop::options_description& desc) {
	bop::variables_map vm;
	bop::store(bop::parse_command_line(argc, argv, desc), vm);
	bop::notify(vm);
	return vm;
}
//////////////////////////////////////////////////////////////////////

string displayWeather(NWSDataRetriever& nwsDataRetriever) {
	Cache cache;

	Weather lw = nwsDataRetriever.getLocalWeather();
	Weather cw = nwsDataRetriever.getCacheWeather(cache);
	NWSDataCombiner::combine(lw, cw);

	string weather = DisplayFormatter::formatWeather(lw);

	cache.save(lw);

	return weather;
}

int execMain(bop::variables_map& vm) {
	try {
		NWSDataRetriever nwsDataRetriever( vm["lat"].as<float>(), vm["lon"].as<float>() );

		if (vm.count("json"))
			cout << nwsDataRetriever.getLocalWeatherJSON() << endl;
		else
			cout << displayWeather(nwsDataRetriever) << std::flush;  // no endl facilitates use in Conky display
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << endl;
		return -1;
	}
	return 0;
}

int main(int argc, char* argv[]) {

	bop::options_description desc = initDescription();
	bop::variables_map vm = initVariablesMap(argc, argv, desc);

	if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}

	return execMain(vm);
}
