/*
 * MyMath.h
 *
 *  Created on: Aug 27, 2022
 *      Author: David Yockey
 */

#ifndef SRC_MYMATH_H_
#define SRC_MYMATH_H_

class MyMath {
private:
	static void okPrecision (std::string methodname, int precision);

public:
	MyMath();

	static float  roundFloat  (float  f, int precision=0);
	static double roundDouble (double d, int precision=0);

	virtual ~MyMath();
};

#endif /* SRC_MYMATH_H_ */
