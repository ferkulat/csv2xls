#!/bin/bash
 
rm -rf $(find $(dirname ${0}) -name ".deps" )
rm -f  $(find $(dirname ${0}) -name "Makefile" )
rm -f  $(find $(dirname ${0}) -name "Makefile.in" )
rm -f  $(find $(dirname ${0}) -name ".dirstamp" )
rm -f  $(find $(dirname ${0}) -name "*.o" )

rm -rf autom4te.cache
rm -f  aclocal.m4
rm -f  config.* configure
rm -f  depcomp  install-sh missing stamp-h1
rm -f  test-driver
