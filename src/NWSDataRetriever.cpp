/*
 * NWSDataRetriever.cpp
 *
 *  Created on: Aug 24, 2022
 *      Author: David Yockey
 */

#include <cstdlib>

#include "NWSDataRetriever.h"
#include "Curler.h"
#include "MyMath.h"
#include "Cache.h"

namespace bjs = boost::json;


///// private: ///////////////////////////////////////////////////////

string NWSDataRetriever::fv2str (float f) {
	// Converts f to a string representation of a 4-significant-figure value,
	// i.e. the limit of precision imposed by the National Weather Service API,
	// to use in constructing a URL
	std::ostringstream ss;
	ss << MyMath().roundFloat(f, 4);
	return ss.str();
}

///// public: ////////////////////////////////////////////////////////

NWSDataRetriever::NWSDataRetriever(float lat, float lon) {
	this->lat = fv2str(lat);
	this->lon = fv2str(lon);
}

string NWSDataRetriever::getLocalWeatherJSON() {
	fieldsmap httpHeaderFields = { {CURLOPT_USERAGENT, "lwnws"}, {CURLOPT_HTTPHEADER, "Accept:application/geo+json"} };
	Curler curl(&httpHeaderFields);

	string pointsJSON = curl.pull("https://api.weather.gov/points/" + lat + ',' + lon);
	bjs::value parsed_points = parser.parse(pointsJSON);
	string stationsURL = parsed_points.at("properties").at("observationStations").as_string().c_str();

	string stationsJSON = curl.pull(stationsURL);
	bjs::value parsed_stations = parser.parse(stationsJSON);
	string stationidURL = parsed_stations.at("features").at(0).at("id").as_string().c_str();

	string weatherJSON = curl.pull(stationidURL + "/observations/latest");
	return weatherJSON;
}

Weather NWSDataRetriever::getLocalWeather() {
	string weatherJSON = getLocalWeatherJSON();
	bjs::value parsed_weather = parser.parse(weatherJSON);
	return Weather(parsed_weather);
}

Weather NWSDataRetriever::getCacheWeather(Cache& cache) {
	Weather weather;
	cache.load(weather);
	return weather;
}
