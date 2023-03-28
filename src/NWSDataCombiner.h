/*
 * NWSDataCombiner.h
 * - Class to combine cached weather data with current weather data where
 *   current weather data values are missing or faulty
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

#ifndef SRC_NWSDATACOMBINER_H_
#define SRC_NWSDATACOMBINER_H_

#include <map>
#include <utility>

#include "Weather.h"

typedef void (*prophandler)(std::string, Weather&, Weather&);
typedef std::map<std::string, prophandler> handlermap;

class NWSDataCombiner {
private:
	static handlermap prophandlers;
	static string getQC (string property, Weather& currentweather);
	static bool is_value_null (string property, Weather& currentweather);

	// property handlers
	static void sansQC(string property, Weather& currentweather, Weather& cachedweather);
	static void windgust(string property, Weather& currentweather, Weather& cachedweather);
	static void defaulthandle(string property, Weather& currentweather, Weather& cachedweather);

public:
	NWSDataCombiner();

	static void combine(Weather& currentweather, Weather& cachedweather);

	virtual ~NWSDataCombiner() {};
};

#endif /* SRC_NWSDATACOMBINER_H_ */
