/*
 * jsonutils.h
 *
 *  Created on: Dec 8, 2022
 *      Author: David
 */

#ifndef JSONUTIL_HPP_
#define JSONUTIL_HPP_

#include <string>
#include <boost/json/object.hpp>

using std::string;

namespace bjs = boost::json;

namespace jsonutil {
	bjs::value getvalue(bjs::object& obj, std::vector<string>& props);
	string     getstring(bjs::object& obj, std::vector<string> props);
}

#endif /* JSONUTIL_HPP_ */
