/*
 * NWSDataCombiner.h
 *
 *  Created on: Dec 4, 2022
 *      Author: David Yockey
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
