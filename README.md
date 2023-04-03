# lwnws

Local Weather from the U.S. National Weather Service

## Description

**lwnws** determines the latest weather conditions at the U.S. National
Weather Service observation station closest to a location specified by a
given latitude and longitude. The weather conditions are based on data
provided by the NWS public API. The output is formatted and printed to
standard output; for example:

    $ lwnws --lat 41.94808 --lon -87.65634
    Cloudy
    53°F  1009hPa  53%RH  Wind E 7mph

The program includes caching of the output weather data and substitution
of cached values for missing or faulty values included in updated data
provided by the API. 

## Command Line Arguments
    -h, --help             Generate help message.
    
    -j, --json             Return JSON data for current weather at specified
                           location, modified by cached data as needed.
                      
    -r, --rawjson          Return JSON data for current weather at specified
                           location, unmodified (i.e. direct from NWS API).
                      
    --lat arg (= 38.99322) Latitude
    
    --lon arg (=-77.03207) Longitude
  
  If latitude and longitude values are not provided, default values
  (38.99322, -77.03207) specifying the location of the U.S. National
  Weather Service headquarters are used.

## Requirements

The following libraries are required:

* libcurl
* Boost Program Options
* Boost JSON

If the version of Boost packages on your system or in your repository
are lower than 1.75.0, JSON support will not be available. In that
event, you will need to:

1. Download Boost 1.75.0 or later from https://www.boost.org.
2. Decompress the downloaded compressed file into a convenient location
(e.g. `~/opt`).
3. Add the path to the decompressed Boost directory as an include option to
the `configure` command in the build process, as outlined below.

## Build

First, open a terminal and navigate to the top-level directory of the cloned
repository or decompressed file.

Then, if you downloaded a later version of Boost as discussed under
**Requirements** above, run `configure` with the path to the Boost directory as
an include option, as in the following example (where Boost 1.76.0 has been
decompressed into directory `opt` in home directory `myhome` and has the name
`boost_1_76_0`):

    ./configure -I/home/myhome/opt/boost_1_76_0

Otherwise, simply run the command:

    ./configure

After `configure` completes, run the command:

    make

Finally, if you want to install the software so it's available systemwide,
run the command:

    sudo make install

## Removal

If the program was not installed as described above, simply delete the
top-level directory of the cloned repository or decompressed file.

Otherwise, return to the top-level directory of the cloned repository
or decompressed file, and from there run the command:

    sudo make uninstall

Then, delete the top-level directory.
