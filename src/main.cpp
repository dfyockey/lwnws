/*
 * main.cpp
 *
 *  Created on: Jul 31, 2022
 *      Author: David Yockey
 */

#include <stdio.h>
#include <iostream>

#include <boost/program_options.hpp>
#include <curl/curl.h>

#include "Curler.h"

namespace bop = boost::program_options;

using std::cout;
using std::endl;
using std::to_string;

string fv2str (bop::variables_map& vm, string arg) {
 // Convert a float cmdline arg value to a `setprecision(4)` string representation
 // as required by the National Weather Service API.
	std::ostringstream ss;
	ss << static_cast<float>( static_cast<int>( vm[arg].as<float>() * 10000 + .5 ) ) / 10000;
	return ss.str();
}


///// Initialization of Program Options //////////////////////////////
bop::options_description initDescription() {
	bop::options_description desc("\nGets the latest weather conditions at the\n"
				                      "U.S. National Weather Service observation station\n"
				                      "closest to the specified location.\n\n"
				                      "  Command Line Options");

	desc.add_options()
		( "help", " generate help message" )
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


int execMain(bop::variables_map& vm) {
	try {
		fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, "lwnws"}, {CURLOPT_HTTPHEADER, "Accept:application/geo+json"} };
		Curler curl(&httpHeaderFields);

		cout << curl.pull("https://api.weather.gov/points/" + fv2str(vm,"lat") + ',' + fv2str(vm,"lon")) << endl;
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}

	return 0;
}


int main(int argc, char* argv[]) {

	///// Program Options ////////////////////////////////////////////////
	bop::options_description desc = initDescription();
	bop::variables_map vm = initVariablesMap(argc, argv, desc);

	if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}
	//////////////////////////////////////////////////////////////////////

	return execMain(vm);
}
