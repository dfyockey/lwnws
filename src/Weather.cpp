/*
 * Weather.cpp
 *
 *  Created on: Aug 26, 2022
 *      Author: David Yockey
 */

#include "Weather.h"

#include <array>

///// private: ///////////////////////////////////////////////////////

double Weather::C2F(double degC) {
	double degF = ((9.0 * degC) / 5.0) + 32.0;
	return degF;
}

double Weather::kph2mph(double kph) {
	double mph = kph / 1.60934;
	return mph;
}

double Weather::toDouble(const boost::json::value& v) {
	return boost::json::value_to<double>(v);
}

double Weather::getDouble(string prop) {
	return toDouble(at("properties").at(prop).at("value"));
}

double Weather::roundDouble(string prop, int precision /*=2*/) {
	return MyMath().roundDouble( getDouble(prop), precision);
}

string Weather::getString(string prop) {
	return at("properties").at(prop).as_string().c_str();
}

bool Weather::qc(string prop, string qcValue) {
	return (at("properties").at(prop).at("qualityControl").as_string() == qcValue);
}

double Weather::windSetCalm() {
	double speed = 0;

	try {
		speed = getDouble("windSpeed");
		calm = (speed == 0);
	}
	catch (...) {
		calm = false;
	}

	return speed;
}

string Weather::windNamedDir() {
	std::array<string,8> namedDir = {"N","NE","E","SE","S","SW","W","NW"};

	/*
	 * Angle of a North wind is in the range from 337.5° to 22.5°, bridging the 0° angle.
	 * Normalize the wind angle by adding 22.5° to simplify calculation to select the wind direction name.
	 */
	const float angleNormalization = 22.5;
	float angle = static_cast<float>(at("properties").at("windDirection").at("value").as_int64()) + angleNormalization;
	if (angle >= 360)
		angle = MyMath().roundFloat(angle-360, 0);

	// Calculation to select the wind direction name.
	int index = angle/45.0;

	return namedDir[index];
}

double Weather::windSpeed(int precision, bool kph /*=true*/) {
	double speed = windSetCalm();	// Called in both windSpeed and windDir methods
									// since user may call speed or direction methods in any order.
	if (!calm) {
		if (kph)
			speed = MyMath().roundDouble(speed, precision);
		else //mph
			speed = MyMath().roundDouble(kph2mph(speed), precision);
	}

	return speed;
}

double Weather::windGust(int precision, bool kph) {
	double gust = 0;

	if ( !qc("windGust","Z") && !qc("windGust","X") ) {
		if (kph)
			gust = roundDouble("windGust", precision);
		else //kph
			gust = MyMath().roundDouble(kph2mph(getDouble("windGust")), precision);
	}

	return gust;
}

///// public: ////////////////////////////////////////////////////////

string Weather::description() {
	return getString("textDescription");
}

string Weather::timestamp() {
	return getString("timestamp");
}

double Weather::humidity(int precision /*=2*/) {
	return roundDouble("relativeHumidity", precision);
}

double Weather::tempC(int precision /*=2*/) {
	return roundDouble("temperature", precision);
}

double Weather::tempF(int precision/*=2*/) {
	return MyMath().roundDouble( C2F(getDouble("temperature")), precision );
}

int Weather::pressurehPa() {
	return pressurePa()/100;
}

int Weather::pressurePa() {
	return at("properties").at("barometricPressure").at("value").as_int64();
}

string Weather::windDir() {
	string result;

	windSetCalm();		// Called in both windSpeed and windDir methods since
						// user may call speed and direction methods in any order.

	if (calm)
		result = "Calm";
	else if (qc("windDirection","Z"))
		result = "Vrbl";
	else if (qc("windDirection","X"))
		result = "Unkn";
	else
		result = windNamedDir();

	return result;
}

double Weather::windSpeedkph(int precision) {
	return windSpeed(precision, true);
}

double Weather::windSpeedmph(int precision) {
	return windSpeed(precision, false);
}

double Weather::windGustkph(int precision) {
	return windGust(precision, true);
}

double Weather::windGustmph(int precision) {
	return windGust(precision, false);
}

