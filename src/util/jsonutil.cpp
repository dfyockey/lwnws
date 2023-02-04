/*
 * jsonutils.cpp
 *
 *  Created on: Dec 8, 2022
 *      Author: David
 */

#include "jsonutil.hpp"

bjs::value jsonutil::getvalue(bjs::object& obj, std::vector<string>& props) {
	bjs::value val = obj;

	for ( auto prop : props ) {
		val = val.at(prop);
	}

	return val;
}

std::string jsonutil::getstring(bjs::object& obj, std::vector<string> props) {
	return getvalue(obj, props).as_string().c_str();
}
