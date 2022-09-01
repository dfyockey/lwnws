# lwnws

Local Weather from the U.S. National Weather Service

## Description

**lwnws** is intended to retrieve the latest weather conditions at the
U.S. National Weather Service observation station closest to a specified location. That
location is specified by providing its latitude and longitude.

## Command Line Arguments
  -h [ --help ]           generate help message
  
  -j [ --json ]           return unparsed JSON data for the specified location
  
  --lat arg (= 38.99322)  latitude
  
  --lon arg (=-77.03207)  longitude

## Requirements

The following libraries are required:
* libcurl
* Boost Program Options
* Boost JSON


## Compilation

After cloning the repo, `cd` into the `src` directory. Then run the following, replacing `/usr/lib64` with the location of the libraries on your system if needed:

`g++ -L/usr/lib64 -lcurl -lboost_program_options -lboost_json -o lwnws main.cpp Curler.cpp Curler.h Weather.cpp Weather.h`