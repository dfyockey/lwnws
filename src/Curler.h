/*
 * Curler.h
 * - Class to retrieve data from the internet via curl
 *
 * Copyright 2022 David Yockey
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

#ifndef SRC_CURLER_H_
#define SRC_CURLER_H_

#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>

#include <curl/curl.h>

using std::string;
using std::ostringstream;

const int null = 0;

typedef std::multimap<CURLoption,string> fieldsmap;

// Curler : Manages pulling resources from URLs using the libcurl Easy interface

class Curler {
private:
	CURL* curl;
	struct curl_slist *customHeaders;
	fieldsmap httpHeaderFields;

	void setCurlOptions(CURL* curl, string url, ostringstream& ossCurlResponse);
	void setHttpHeaderFields(fieldsmap fields);

	static size_t write_callback(char* data, size_t size, size_t nmemb, void* userdata);

public:
	Curler(fieldsmap* fields=0);	// key-value pairs passed to the constructor in the fieldsmap
									// are persistently stored in the CURL object

	string pull(string url);

	virtual ~Curler();				// curl_easy_cleanup is executed in the dtor,
									// so the user doesn't need to remember to call it
};

class setopt_error : public std::runtime_error {
	public:
		setopt_error(CURLcode res) : std::runtime_error(string("curl_easy_setopt() failed: ") + curl_easy_strerror(res) ) {}
};

#endif /* SRC_CURLER_H_ */
