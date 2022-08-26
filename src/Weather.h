/*
 * Weather.h
 *
 *  Created on: Aug 26, 2022
 *      Author: David
 */

#ifndef SRC_WEATHER_H_
#define SRC_WEATHER_H_

#include <boost/json/object.hpp>

class Weather: public boost::json::object {
private:
    double C2F(double degC);

public:
	Weather(boost::json::value parsed_weather) : object(parsed_weather.as_object()) {};

	double tempC() { return at("properties").at("temperature").at("value").as_double(); }
	double tempF() { return C2F(tempC()); }

	virtual ~Weather();
};

#endif /* SRC_WEATHER_H_ */
