/*
 * DisplayFormatter.cpp
 *
 *  Created on: Feb 6, 2023
 *      Author: David
 */

#include "DisplayFormatter.h"

#include <iostream>

#include <boost/json.hpp>
#include <boost/json/object.hpp>
#include <boost/json/value.hpp>

void DisplayFormatter::printWeatherObject(Weather& w) {
	// This function is provided for debugging

	for (auto kv : w)
		std::cout << kv.key() << ":" << kv.value() << "\n";

	std::cout << std::flush;
}

string DisplayFormatter::formatWeather(Weather& w) {
	std::stringstream ss;
	const string leftmargin = " ";
	const string spacer = "  ";

	ss << leftmargin << w.description() << spacer << (( w.timestamp().size() > 11 ) ? w.timestamp().substr(11,5) : "?") << " UTC" << "\n";
	ss << leftmargin << w.tempF(0) << "°F" << spacer << w.pressurehPa() << "hPa" << spacer << w.humidity(0) << "%RH" << spacer;

	string winddir = w.windDir();
	ss << "Wind " << winddir;
	if (winddir != "Calm") {
		ss << " " << w.windSpeedmph(0) << "mph";
		double windGust = w.windGustmph(0);
		if ( windGust > 0 )
			ss << " G " << windGust << "mph";
	}
	ss << "\n";

	return ss.str();
}
