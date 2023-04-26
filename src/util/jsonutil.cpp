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
#include <boost/json.hpp>

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

////////////////////////////////////////////////////////////////////////////////////////////////////
// The following implementation of pretty_print is from the boost::json library examples at
// https://www.boost.org/doc/libs/1_76_0/libs/json/doc/html/json/examples.html#json.examples.pretty

void jsonutil::pretty_print( std::ostream& os, bjs::value const& jv, std::string* indent) {
    std::string indent_;
    if(! indent)
        indent = &indent_;
    switch(jv.kind())
    {
    case bjs::kind::object:
    {
        os << "{\n";
        indent->append(4, ' ');
        auto const& obj = jv.get_object();
        if(! obj.empty())
        {
            auto it = obj.begin();
            for(;;)
            {
                os << *indent << bjs::serialize(it->key()) << " : ";
                pretty_print(os, it->value(), indent);
                if(++it == obj.end())
                    break;
                os << ",\n";
            }
        }
        os << "\n";
        indent->resize(indent->size() - 4);
        os << *indent << "}";
        break;
    }

    case bjs::kind::array:
    {
        os << "[\n";
        indent->append(4, ' ');
        auto const& arr = jv.get_array();
        if(! arr.empty())
        {
            auto it = arr.begin();
            for(;;)
            {
                os << *indent;
                pretty_print( os, *it, indent);
                if(++it == arr.end())
                    break;
                os << ",\n";
            }
        }
        os << "\n";
        indent->resize(indent->size() - 4);
        os << *indent << "]";
        break;
    }

    case bjs::kind::string:
    {
        os << bjs::serialize(jv.get_string());
        break;
    }

    case bjs::kind::uint64:
        os << jv.get_uint64();
        break;

    case bjs::kind::int64:
        os << jv.get_int64();
        break;

    case bjs::kind::double_:
        os << jv.get_double();
        break;

    case bjs::kind::bool_:
        if(jv.get_bool())
            os << "true";
        else
            os << "false";
        break;

    case bjs::kind::null:
        os << "null";
        break;
    }

    if(indent->empty())
        os << "\n";
}
