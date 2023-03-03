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

handlermap NWSDataCombiner::prophandlers = {
	{"timestamp", &sansQC},
	{"textDescription", &sansQC},
	{"windGust", &windgust}
};

string NWSDataCombiner::getQC(string property, Weather& currentweather) {
	return jsonutil::getstring(currentweather, {"properties", property, "qualityControl"});
}

// handler for properties that have no quality control descriptors
void NWSDataCombiner::sansQC(string property, Weather& currentweather, Weather& cachedweather) {
	if ( currentweather.getString(property).empty() )
		currentweather["properties"].as_object()[property] = cachedweather.getString(property);
}

// handler to insure that windGust value is only copied from cache when a current windSpeed is not valid
//
// Note: An invalid windGust is the normal condition when the wind is not currently gusting, so there is
// no way to know if there should be a windGust in the current data if windSpeed *is* valid but no valid
// windGust is provided. Consequently, we should allow copying a windGust value from the cache to
// substitute for an invalid value only when there is no valid windSpeed in the current data.
//
void NWSDataCombiner::windgust(string property, Weather& currentweather, Weather& cachedweather) {
	string qc = getQC("windSpeed", currentweather);

	if ( qc == "Z" || qc == "X" )
		defaulthandle(property, currentweather, cachedweather);
}

bool NWSDataCombiner::is_value_null(string property, Weather& currentweather) {
	std::vector<string> v = {"properties", property, "value"};
	bjs::value val = jsonutil::getvalue(currentweather, v);
	return val.is_null();
}

void NWSDataCombiner::defaulthandle(string property, Weather& currentweather, Weather& cachedweather) {
	string qc = getQC(property, currentweather);

	// substitute cached data if current data has no quality control ("Z") or is rejected/erroneous ("X")
	if ( qc == "Z" || qc == "X" || qc == "Q" || is_value_null(property, currentweather) ) {
		currentweather["properties"].as_object()[property].as_object()["value"] = cachedweather.at("properties").at(property).at("value");
		currentweather["properties"].as_object()[property].as_object()["qualityControl"] = cachedweather.at("properties").at(property).at("qualityControl");
	}
}

///// public: ////////////////////////////////////////////////////////

NWSDataCombiner::NWSDataCombiner() {}

void NWSDataCombiner::combine(Weather& currentweather, Weather& cachedweather) {
	for (std::string property : currentweather.properties) {
		if (prophandlers.count(property) > 0) {
			// handle properties needing special treatment
			prophandlers[property](property, currentweather, cachedweather);
		} else {
			// handle remaining properties
			defaulthandle(property, currentweather, cachedweather);
		}
	}
}
