/*
 * jsonutils.cpp
 * - Implementation of Namespace jsonutils functions
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

#include "jsonutil.hpp"

/*
 * In the following two functions, "obj" contains the JSON object from which to
 * get a value, and "props" is an array of properties defining the hierarchical
 * path leading to the desired JSON value, where the last item in the array is
 * the JSON value desired.
 *
 */

bjs::value jsonutil::getvalue(bjs::object& obj, vector<string>& props) {
	bjs::value val = obj;

	// Drill down through JSON hierarchy until desired value is found
	for ( auto prop : props ) {
		val = val.at(prop);
	}

	return val;
}

std::string jsonutil::getstring(bjs::object& obj, vector<string> props) {
	return getvalue(obj, props).as_string().c_str();
}
