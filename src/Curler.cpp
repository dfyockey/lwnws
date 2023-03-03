/*
 * Curler.cpp
 *
 *  Created on: Aug 3, 2022
 *      Author: David Yockey
 */

#include "Curler.h"

using std::runtime_error;

///// private ////////////////////////////////////////////////////////

void Curler::setCurlOptions(CURL* curl, string url, ostringstream& ossCurlResponse) {
	CURLcode res;

	// set minimal options
	do {
		if( (res = curl_easy_setopt( curl, CURLOPT_URL, url.c_str() )) != CURLE_OK ) break;
		if( (res = curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_callback )) != CURLE_OK ) break;
		if( (res = curl_easy_setopt( curl, CURLOPT_WRITEDATA, reinterpret_cast<void*>(&ossCurlResponse) )) != CURLE_OK ) break;
	} while (false);

	if ( res != CURLE_OK )
		throw setopt_error(res);
}

void Curler::setHttpHeaderFields(fieldsmap fields) {
	CURLcode res;
	bool customize = false;

	for (const auto& [key,value] : fields) {

		if( key == CURLOPT_HTTPHEADER ) {
			customHeaders = curl_slist_append(customHeaders, value.c_str());
			customize = true;
			continue;
		}

		if( (res = curl_easy_setopt( curl, key, value.c_str() )) != CURLE_OK )
			throw setopt_error(res);
	}

	if ( customize && (res = curl_easy_setopt( curl, CURLOPT_HTTPHEADER, customHeaders)) != CURLE_OK )
		throw setopt_error(res);
}

size_t Curler::write_callback(char* data, size_t size, size_t nmemb, void* userdata) {
	size_t datasize = size * nmemb;

	ostringstream* oss = reinterpret_cast<ostringstream*>(userdata);
	*oss << string(data, datasize);

	return datasize;
}

///// public /////////////////////////////////////////////////////////

Curler::Curler(fieldsmap* fields) {
	if ( !(curl = curl_easy_init()) )
		throw std::runtime_error(string("curl_easy_init() failed"));

	customHeaders = 0;

	if (fields)
		setHttpHeaderFields(*fields);
}

string Curler::pull(string url) {
	CURLcode res;
	ostringstream ossCurlResponse;

	try {
		setCurlOptions(curl, url, ossCurlResponse);

		// Perform the request, where res will get the return code, and then check for errors
		if( (res = curl_easy_perform(curl)) != CURLE_OK)
			throw std::runtime_error(string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
	}

	// Return a string containing the retrieved data requested or an empty string
    return ossCurlResponse.str();
}

Curler::~Curler() {
	if (customHeaders)
		curl_slist_free_all(customHeaders);

    curl_easy_cleanup(curl);
}
