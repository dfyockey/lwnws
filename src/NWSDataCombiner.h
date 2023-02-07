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

public:
	NWSDataCombiner();

	static void combine(Weather& currentweather, Weather& cachedweather);

	virtual ~NWSDataCombiner() {};
};

#endif /* SRC_NWSDATACOMBINER_H_ */
