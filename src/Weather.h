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

using std::string;

class Weather: public boost::json::object {
private:
	bool calm;

    double C2F		(double degC);
    double kph2mph	(double kph);

    double toDouble		(const boost::json::value& v);
    double getDouble	(string prop);
    double roundDouble	(string prop, int precision=2);

    string getString (string prop);

    bool qc (string prop, string qcValue);

    double windSetCalm	();
    string windNamedDir	();
	double windSpeed	(int precision, bool kph=true);
	double windGust		(int precision, bool mph);

public:
	Weather(boost::json::value parsed_weather) : object(parsed_weather.as_object()), calm(false) {}

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
