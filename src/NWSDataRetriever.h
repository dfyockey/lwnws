/*
 * NWSDataRetriever.h
 *
 *  Created on: Aug 24, 2022
 *      Author: David
 */

#ifndef SRC_NWSDATARETRIEVER_H_
#define SRC_NWSDATARETRIEVER_H_

#include <string>
#include <boost/json.hpp>
#include "Weather.h"

using std::string;
namespace bjs = boost::json;

class NWSDataRetriever {
private:
	string lat;
	string lon;
	bjs::parser jsonParser;

	string fv2str (float f);
	bjs::value parse(string json);

public:
	NWSDataRetriever(float lat, float lon);

	string	getLocalWeatherJSON();
	Weather getLocalWeather();

	virtual ~NWSDataRetriever();
};

#endif /* SRC_NWSDATARETRIEVER_H_ */
