/*
 * Curler.h
 *
 *  Created on: Aug 3, 2022
 *      Author: David Yockey
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
public:
	Curler(fieldsmap* fields=0);	// key-value pairs passed to the constructor in the fieldsmap
									// are persistently stored in the CURL object

	string pull(string url);

	virtual ~Curler();				// curl_easy_cleanup is executed in the dtor,
									// so the user doesn't need to remember to call it

private:
	CURL* curl;
	struct curl_slist *customHeaders;
	fieldsmap httpHeaderFields;

	void setCurlOptions(CURL* curl, string url, ostringstream& ossCurlResponse);
	void setHttpHeaderFields(fieldsmap fields);

	static size_t write_callback(char* data, size_t size, size_t nmemb, void* userdata);
};

class setopt_error : public std::runtime_error {
	public:
		setopt_error(CURLcode res) : std::runtime_error(string("curl_easy_setopt() failed: ") + curl_easy_strerror(res) ) {}
};

#endif /* SRC_CURLER_H_ */
