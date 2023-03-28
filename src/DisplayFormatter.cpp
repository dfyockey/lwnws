/*
 * DisplayFormatter.cpp
 * - Implementation of Namespace DisplayFormatter functions
 *
 * Copyright 2023 David Yockey
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

	ss << leftmargin << w.description() << "\n";
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
