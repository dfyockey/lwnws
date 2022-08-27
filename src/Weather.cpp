/*
 * Weather.cpp
 *
 *  Created on: Aug 26, 2022
 *      Author: David
 */

#include "Weather.h"

double Weather::C2F(double degC) {
	double degF = ((9.0 * degC) / 5.0) + 32.0;
	return degF;
}

double Weather::toDouble(const boost::json::value& v) {
	return boost::json::value_to<double>(v);
}

/*
Weather::Weather() {
	// TODO Auto-generated constructor stub
}

Weather::~Weather() {
	// TODO Auto-generated destructor stub
}
*/

