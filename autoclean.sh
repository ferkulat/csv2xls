#!/bin/bash
rm -f src/*.o
rm -f src/*.lo
rm -f src/*.la
rm -f src/.dirstamp
rm -rf src/.deps
rm -rf testing/.deps
rm -rf testing/*.{o,la,lo}
rm -rf testing/Makefile{,.in}
rm -rf autom4te.cache
rm -rf bin/*
rm aclocal.m4
rm ar-lib config.guess config.h config.h.in config.log config.status config.sub configure
rm  depcomp  install-sh   Makefile Makefile.in missing stamp-h1
rm src/Makefile.in
rm src/Makefile
rm cppUnit/Makefile.in
rm cppUnit/Makefile
rm -rf doc/html doc/latex doc/Makefile doc/Makefile.in
