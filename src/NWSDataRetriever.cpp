/*
 * NWSDataRetriever.cpp
 *
 *  Created on: Aug 24, 2022
 *      Author: David
 */

#include "NWSDataRetriever.h"
#include "Curler.h"


///// private: ///////////////////////////////////////////////////////

string NWSDataRetriever::fv2str (float f) {
	// Converts f to a string representation of a 4-significant-figure value,
	// i.e. the limit of precision imposed by the National Weather Service API,
	// to use in constructing a URL
	std::ostringstream ss;
	ss << static_cast<float>( static_cast<int>( f * 10000 + .5 ) ) / 10000;
	return ss.str();
}

boost::json::value NWSDataRetriever::parse(string json) {
	jsonParser.reset();
	jsonParser.write(json);
	return jsonParser.release();
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
	bjs::value parsed_points = parse(pointsJSON);
	string stationsURL = parsed_points.at("properties").at("observationStations").as_string().c_str();

	string stationsJSON = curl.pull(stationsURL);
	bjs::value parsed_stations = parse(stationsJSON);
	string stationidURL = parsed_stations.at("features").at(0).at("id").as_string().c_str();

	string weatherJSON = curl.pull(stationidURL + "/observations/latest");
	return weatherJSON;
}

bjs::object NWSDataRetriever::getLocalWeather() {
	string weatherJSON = getLocalWeatherJSON();
	bjs::value parsed_weather = parse(weatherJSON);
	return parsed_weather.as_object();
}

NWSDataRetriever::~NWSDataRetriever() {
	// TODO Auto-generated destructor stub
}

