/*
 * jsonutils.cpp
 *
 *  Created on: Dec 8, 2022
 *      Author: David
 */

#include "jsonutil.hpp"

/*
 * In the following two functions, "obj" contains the JSON object from which to
 * get a value, and "props" is an array of properties defining the hierarchical
 * path leading to the desired JSON value, where the last item in the array is
 * the JSON value desired.
 *
 */

bjs::value jsonutil::getvalue(bjs::object& obj, std::vector<string>& props) {
	bjs::value val = obj;

	// Drill down through JSON hierarchy until desired value is found
	for ( auto prop : props ) {
		val = val.at(prop);
	}

	return val;
}

std::string jsonutil::getstring(bjs::object& obj, std::vector<string> props) {
	return getvalue(obj, props).as_string().c_str();
}
