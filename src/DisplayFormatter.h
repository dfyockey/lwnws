/*
 * DisplayFormatter.h
 *
 *  Created on: Feb 6, 2023
 *      Author: David
 */

#ifndef SRC_DISPLAYFORMATTER_H_
#define SRC_DISPLAYFORMATTER_H_

#include "Weather.h"

namespace DisplayFormatter {
	string formatWeather(Weather& w);
	void   printWeatherObject(Weather& w);	// provided for debugging
};

#endif /* SRC_DISPLAYFORMATTER_H_ */
