/*
 * Parser.cpp
 *
 *  Created on: Sep 29, 2022
 *      Author: David Yockey
 */

#include "Parser.h"

///// public /////////////////////////////////////////////////////////

boost::json::value Parser::parse(std::string json) {
	jsonParser.reset();
	jsonParser.write(json);
	return jsonParser.release();
}


