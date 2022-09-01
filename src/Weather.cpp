/*
 * Weather.cpp
 *
 *  Created on: Aug 26, 2022
 *      Author: David
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

string Weather::windNamedDir () {
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

double Weather::windSpeed(int precision, bool kph) {
	double speed = getDouble("windSpeed");
	calm = (speed == 0);

	if (calm) {
		speed = 0;
	}
	else {
		if (kph)
			speed = MyMath().roundDouble(speed, precision);
		else
			speed = MyMath().roundDouble(kph2mph(speed), precision);
	}

	return speed;
}

/*
double Weather::toDouble(const boost::json::value& v) {
	return boost::json::value_to<double>(v);
}
*/


///// public: ////////////////////////////////////////////////////////

string Weather::windDir() {
	string result;

	calm = (getDouble("windSpeed") == 0);

	if (calm)
		result = "Calm";
	else if (qc("windDirection","Z"))
		result = "Vrbl";
	else
		result = windNamedDir();

	return result;
}

double Weather::windGustkph(int precision) {
	//return (qc("windGust","Z")) ? 0 : roundDouble("windGust", precision);

	if (qc("windGust","Z"))
		return 0;

	return roundDouble("windGust", precision);
}

double Weather::windGustmph(int precision) {
	if (qc("windGust","Z"))
		return 0;

	return MyMath().roundDouble(kph2mph(getDouble("windGust")), precision);
}

/*
Weather::Weather() {
	// TODO Auto-generated constructor stub
}

Weather::~Weather() {
	// TODO Auto-generated destructor stub
}
*/

