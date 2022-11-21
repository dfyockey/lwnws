/*
 * Parser.hpp
 *
 *  Created on: Sep 29, 2022
 *      Author: David Yockey
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <string>
#include <boost/json.hpp>

namespace bjs = boost::json;

class Parser {
private:
	bjs::parser jsonParser;

public:
	bjs::value parse(std::string json);
};

#endif /* SRC_PARSER_H_ */
