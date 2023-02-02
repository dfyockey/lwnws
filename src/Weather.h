/*
 * Weather.h
 *
 *  Created on: Aug 26, 2022
 *      Author: David Yockey
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
	bool calm;

    double C2F		(double degC);
    double kph2mph	(double kph);

    double toDouble		(const boost::json::value& v);
    double getDouble	(string prop);
    double roundDouble	(string prop, int precision=2);

    bool qc (string prop, string qcValue);

    double windSetCalm	();
    string windNamedDir	();
	double windSpeed	(int precision, bool kph=true);
	double windGust		(int precision, bool mph);

public:
	Weather() : object(), calm(false) {}
	Weather(boost::json::value parsed_weather) : object(parsed_weather.as_object()), calm(false) {}

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
