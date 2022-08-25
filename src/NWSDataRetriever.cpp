/*
 * NWSDataRetriever.cpp
 *
 *  Created on: Aug 24, 2022
 *      Author: David
 */

#include "NWSDataRetriever.h"
#include "Curler.h"


NWSDataRetriever::NWSDataRetriever(float lat, float lon) {
	this->lat = fv2str(lat);
	this->lon = fv2str(lon);
}



std::string NWSDataRetriever::getLocalWeatherJSON() {
	fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, "lwnws"}, {CURLOPT_HTTPHEADER, "Accept:application/geo+json"} };
	Curler curl(&httpHeaderFields);

	return curl.pull("https://api.weather.gov/points/" + lat + ',' + lon);

}

NWSDataRetriever::~NWSDataRetriever() {
	// TODO Auto-generated destructor stub
}

///// Private Methods ////////////////////////////////////////////////

string NWSDataRetriever::fv2str (float f) {
	// Converts f to a string representation of a 4-significant-figure value,
	// i.e. the limit of precision imposed by the National Weather Service API,
	// to use in constructing a URL
	std::ostringstream ss;
	ss << static_cast<float>( static_cast<int>( f * 10000 + .5 ) ) / 10000;
	return ss.str();
}

