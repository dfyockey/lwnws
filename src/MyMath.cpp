/*
 * MyMath.cpp
 * - Class MyMath method implementations
 *
 * Copyright 2022,2023 David Yockey
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

#include <stdexcept>
#include <string>
#include "MyMath.h"

///// private ////////////////////////////////////////////////////////

void MyMath::okPrecision (std::string methodname, int precision) {
	if ( precision < 0 )
		throw std::range_error("Illegal precision < 0 in call to MyMath::" + methodname);
}

///// public /////////////////////////////////////////////////////////

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

