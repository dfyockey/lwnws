/*
 * NWSDataRetriever.cpp
 * - Class NWSDataRetriever method implementations
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

#define BOOST_LOG_DYN_LINK 1

#include <cstdlib>

#include "NWSDataRetriever.h"
#include "Curler.h"
#include "MyMath.h"
#include "Cache.h"

namespace bjs = boost::json;

#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
namespace src = boost::log::sources;


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
	bjs::value parsed_weather;
	try {
		string weatherJSON = getLocalWeatherJSON();
		parsed_weather = parser.parse(weatherJSON);
	} catch (std::runtime_error &e) {
		src::logger lg;
		if (e.what() != "incomplete JSON") {
			throw;
		} else {
			BOOST_LOG(lg) << "Runtime Error : " << e.what() << "\n"
						  << "- NWSDataRetriever::getLocalWeather returning empty Weather object.\n"
						  << "- Continuing execution : Display will rely entirely on cached data.";
		}
	}
	return Weather(parsed_weather);
}

Weather NWSDataRetriever::getCacheWeather(Cache& cache) {
	Weather weather;
	cache.load(weather);
	return weather;
}
