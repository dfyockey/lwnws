/*
 * NWSDataRetriever.h
 *
 *  Created on: Aug 24, 2022
 *      Author: David
 */

#ifndef SRC_NWSDATARETRIEVER_H_
#define SRC_NWSDATARETRIEVER_H_

#include <string>

using std::string;

class NWSDataRetriever {
public:
	NWSDataRetriever(float lat, float lon);

	string getLocalWeatherJSON();

	virtual ~NWSDataRetriever();

private:
	string lat;
	string lon;

	string fv2str (float f);
};

#endif /* SRC_NWSDATARETRIEVER_H_ */
