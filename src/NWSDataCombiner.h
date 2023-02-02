/*
 * NWSDataCombiner.h
 *
 *  Created on: Dec 4, 2022
 *      Author: David Yockey
 */

#ifndef SRC_NWSDATACOMBINER_H_
#define SRC_NWSDATACOMBINER_H_

#include "Weather.h"

class NWSDataCombiner {
private:
	Weather& currentweather;
	Weather& cachedweather;

	void combine();

public:
	NWSDataCombiner(Weather& currentweather, Weather& cacheweather);
	virtual ~NWSDataCombiner() {};
};

#endif /* SRC_NWSDATACOMBINER_H_ */
