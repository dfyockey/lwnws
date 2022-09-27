/*
 * main.cpp
 *
 *  Created on: Jul 31, 2022
 *      Author: David Yockey
 */

#include <stdio.h>
#include <iostream>

#include <boost/json/src.hpp>
#include <boost/program_options.hpp>
#include <curl/curl.h>

#include "Cache.h"
#include "NWSDataRetriever.h"

namespace bop = boost::program_options;

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

// Pass references to nwsDataRetriever to avoid using an undefined instance
// and to avoid need to implement a copy constructor to otherwise get around that problem.

void printWeatherObject(NWSDataRetriever& nwsDataRetriever) {
	boost::json::object localweather = nwsDataRetriever.getLocalWeather();

	for (auto kv : localweather)
		cout << kv.key() << ":" << kv.value() << "\n";

	cout << std::flush;
}

void printWeather(NWSDataRetriever& nwsDataRetriever) {
	Weather lw = nwsDataRetriever.getLocalWeather();
	const string leftmargin = " ", spacer = "  ";

	cout << leftmargin << lw.description() << spacer << lw.timestamp().substr(11,5) << " UTC" << "\n";
	cout << leftmargin << lw.tempF(0) << "°F" << spacer << lw.pressurehPa() << "hPa" << spacer << lw.humidity(0) << "%RH" << spacer;

	string winddir = lw.windDir();
	cout << "Wind " << winddir;
	if (winddir != "Calm") {
		cout << " " << lw.windSpeedmph(0) << "mph";
		double windGust = lw.windGustmph(0);
		if ( windGust > 0 )
			cout << " G " << windGust << "mph";
	}
	cout << endl;

	Cache cached(lw);
	cout << "\n" << cached.dump() << endl;
}

int execMain(bop::variables_map& vm) {
	try {
		NWSDataRetriever nwsDataRetriever( vm["lat"].as<float>(), vm["lon"].as<float>() );

		if (vm.count("json"))
			cout << nwsDataRetriever.getLocalWeatherJSON() << endl;
		else
			printWeather(nwsDataRetriever);
			//printWeatherObject(nwsDataRetriever);
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}


int main(int argc, char* argv[]) {
	cout << argv[0] << endl;
	bop::options_description desc = initDescription();
	bop::variables_map vm = initVariablesMap(argc, argv, desc);

	if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}

	return execMain(vm);
}
