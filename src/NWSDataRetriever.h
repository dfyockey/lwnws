/*
 * NWSDataRetriever.h
 * - Class to retrieve weather data from the NWS or from a cache file
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
