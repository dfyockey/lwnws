/*
 * NWSDataCombiner.cpp
 *
 *  Created on: Dec 4, 2022
 *      Author: David Yockey
 */

#include <string>

//#include <boost/json/string.hpp>

#include "NWSDataCombiner.h"
#include "util/jsonutil.hpp"

///// private: ///////////////////////////////////////////////////////

///// public: ////////////////////////////////////////////////////////

NWSDataCombiner::NWSDataCombiner() {}

void NWSDataCombiner::combine(Weather& currentweather, Weather& cachedweather) {
	for (std::string property : currentweather.properties) {
		/* Handle properties that have no quality control descriptors */
		if ( property == "timestamp" || property == "textDescription" ) {
			if ( currentweather.getString(property).empty() )
				currentweather["properties"].as_object()[property] = cachedweather.getString(property);
		} else {
			/* Handle remaining properties */
			std::string qc = jsonutil::getstring(currentweather, {"properties", property, "qualityControl"});

			// Substitute cached data if current data has no quality control ("Z") or is rejected/erroneous ("X")
			if ( qc == "Z" || qc == "X") {
				currentweather["properties"].as_object()[property].as_object()["value"] = cachedweather.at("properties").at(property).at("value");
				currentweather["properties"].as_object()[property].as_object()["qualityControl"] = cachedweather.at("properties").at(property).at("qualityControl");
			}
		}
	}
}
