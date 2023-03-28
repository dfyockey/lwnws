/*
 * Weather.h
 * - Class for containing weather data parsed from data in JSON format
 *
 * Copyright 2022 David Yockey
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

#ifndef SRC_WEATHER_H_
#define SRC_WEATHER_H_

#include <string>

#include <boost/json/object.hpp>
#include <boost/json/value_to.hpp>

#include "MyMath.h"

namespace bjs = boost::json;
using std::string;

class Weather: public boost::json::object {
private:
    double C2F		(double degC);
    double kph2mph	(double kph);

    double toDouble		(const boost::json::value& v);
    double getDouble	(string prop);
    double roundDouble	(string prop, int precision=2);

    string qualityControl(string prop);

    double windSetCalm	();
    string windNamedDir	();
    double getWindSpeed ();
	double windSpeed	(int precision, bool kph=true);
	double windGust		(int precision, bool mph);

public:
	Weather() : object() {}
	Weather(boost::json::value parsed_weather) : object(parsed_weather.as_object()) {}

	// JSON "properties" of NWS data in the parent boost::json::object used in methods of this class.
	// Purpose: to enable iteration thru the properties in combining current and cached weather.
	const std::array<const string, 8> properties = {
			"timestamp", "textDescription", "temperature", "windDirection",
			"windSpeed", "windGust", "barometricPressure", "relativeHumidity"
	};

    string getString (string prop);		// Needs to be public for access by NWSDataCombiner.

	string description	();
	string timestamp	();
	double humidity		(int precision=2);
	double tempC		(int precision=2);
	double tempF		(int precision=2);
	int    pressurehPa	();
	int    pressurePa	();
	string windDir		();
	double windSpeedkph	(int precision=2);
	double windSpeedmph	(int precision=2);
	double windGustkph	(int precision=2);
	double windGustmph	(int precision=2);

	virtual ~Weather() {}
};

#endif /* SRC_WEATHER_H_ */
