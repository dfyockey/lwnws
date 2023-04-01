/*
 * jsonutils.h
 * - Namespace containing functions to simplify JSON-related
 *   operations
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

#ifndef JSONUTIL_HPP_
#define JSONUTIL_HPP_

#include <string>
#include <vector>
#include <boost/json/object.hpp>

using std::string;
using std::vector;

namespace bjs = boost::json;

namespace jsonutil {
	bjs::value getvalue(bjs::object& obj, vector<string>& props);
	string     getstring(bjs::object& obj, vector<string> props);
}

#endif /* JSONUTIL_HPP_ */
