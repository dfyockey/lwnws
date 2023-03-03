/*
 * NWSDataRetriever.h
 *
 *  Created on: Aug 24, 2022
 *      Author: David Yockey
 */

#ifndef SRC_NWSDATARETRIEVER_H_
#define SRC_NWSDATARETRIEVER_H_

#include <string>
#include <boost/json.hpp>

#include "Weather.h"
#include "Parser.h"
#include "Cache.h"

using std::string;

class NWSDataRetriever {
private:
	string lat;
	string lon;
	Parser parser;
	string fv2str (float f);

public:
	NWSDataRetriever(float lat, float lon);

	string	getLocalWeatherJSON();
	Weather getLocalWeather();
	Weather getCacheWeather(Cache& cache);

	virtual ~NWSDataRetriever() {};
};

#endif /* SRC_NWSDATARETRIEVER_H_ */
