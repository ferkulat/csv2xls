#!/bin/bash
VERSION_FILE=src/version.h
function setver()
{
	echo "#define VERSION \" $1 \"" > $VERSION_FILE
	sed  -i -e "s/\(AC_INIT(.*, \)\(\[.*\]\)\(, \[Marcel.Schneider@coopmasters.de\])\)/\1\[$1\]\3/" configure.ac
}
setver $1
