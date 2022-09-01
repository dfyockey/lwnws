/*
 * MyMath.cpp
 *
 *  Created on: Aug 27, 2022
 *      Author: David
 */

#include <stdexcept>
#include <string>
#include "MyMath.h"

void okPrecision (std::string methodname, int precision) {
	if ( precision < 0 )
		throw std::range_error("Illegal precision < 0 in call to MyMath::" + methodname);
}

MyMath::MyMath() {
	// TODO Auto-generated constructor stub

}

float MyMath::roundFloat(float f, int precision) {
	okPrecision("roundFloat", precision);
	return static_cast<float>( roundDouble(f, precision) );
}

double MyMath::roundDouble(double d, int precision) {
	okPrecision("roundDouble", precision);
	int factor = ( precision > 0 ) ? 10*precision : 1;
	return static_cast<double>( static_cast<int>( d * factor + .5 ) ) / factor;
}

MyMath::~MyMath() {
	// TODO Auto-generated destructor stub
}

