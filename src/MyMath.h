/*
 * MyMath.h
 * - Class containing functions to perform mathematical operations
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
