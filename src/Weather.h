/*
 * Weather.h
 *
 *  Created on: Aug 26, 2022
 *      Author: David
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

    double C2F(double degC);
    double kph2mph(double kph);

    double toDouble(const boost::json::value& v) { return boost::json::value_to<double>(v); }
    double getDouble(string prop) { return toDouble(at("properties").at(prop).at("value")); }
    double roundDouble(string prop, int precision=2) { return MyMath().roundDouble( getDouble(prop), precision); }

    string getString(string prop) { return at("properties").at(prop).as_string().c_str(); }

    bool qc(string prop, string qcValue) { return (at("properties").at(prop).at("qualityControl").as_string() == qcValue); }

    double windSetCalm();
    string windNamedDir ();
	double windSpeed(int precision, bool kph=true);
	double windGust(int precision, bool mph);

public:
	Weather(boost::json::value parsed_weather) : object(parsed_weather.as_object()), calm(false) {}

	string description() { return getString("textDescription"); }

	string timestamp() { return getString("timestamp"); }

	double humidity(int precision=2) { return roundDouble("relativeHumidity", precision); }

	double tempC(int precision=2) { return roundDouble("temperature", precision); }
	double tempF(int precision=2) { return MyMath().roundDouble( C2F(getDouble("temperature")), precision ); }

	int pressurehPa() { return pressurePa()/100; }
	int pressurePa()  { return at("properties").at("barometricPressure").at("value").as_int64(); }

	string windDir();

	double windSpeedkph(int precision=2);
	double windSpeedmph(int precision=2);

	double windGustkph(int precision=2);
	double windGustmph(int precision=2);

	virtual ~Weather() {}
};

#endif /* SRC_WEATHER_H_ */
