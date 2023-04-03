#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([lwnws], [0.0.1], [])
AC_CONFIG_SRCDIR([src/NWSDataCombiner.cpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AX_BOOST_BASE([1.32.0], [], [version 1.32.0 or better of the Boost C++ libraries is required.])
AX_BOOST_PROGRAM_OPTIONS
AC_SEARCH_LIBS(curl_version_info, curl, [])

LIBS="$BOOST_PROGRAM_OPTIONS_LIB $LIBS"

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
