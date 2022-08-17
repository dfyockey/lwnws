# lwnws

Local Weather from the U.S. National Weather Service

## Description

**lwnws** is intended to get the latest weather conditions at the
U.S. National Weather Service observation station closest to a specified location. That
location is specified by providing its latitude and longitude.


### This program is under development and not yet fully functional.
It currently returns only metadata about the given latitude/longitude point in GeoJSON format.


## Requirements

The following libraries are required:
* libcurl
* Boost Program Options


## Compilation

After cloning the repo, `cd` into the `src` directory. Then run the following, replacing `/usr/lib64` with the location of the libraries on your system if needed:

`g++ -L/usr/lib64 -lcurl -lboost_program_options -o lwnws main.cpp Curler.cpp Curler.h`