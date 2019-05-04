### Version: 0.4.0
    * fix issue #13: switched to cmake and doctest
    * updated man page for option -t
    * use C++17
    * libcsv and xlslib will be built as part of the build process
    * csv2xls can now be built with msvc2017 and msvc2019
    * use CheckedCmd for command line parsing

### Version: 0.3.5
    * new option -t for tab as delimiter (thanks to Jakub Macek)

### Version: 0.3.4
    * issue #8: crash on missing input file
                It was not enough to check on minimum one command line parameter.
                Given any valid option it passes this check, and tries to access a
                nonexisting argument.
    * issue #9: crash if inputfile name length is less than 4 chars
    * fix:      If option -H is not set, allow option -l1
 
### Version: 0.3.3
    * issue #5: empty xls file
                Don't write a worksheet to a file, if it is empty or with just a head line.
    * issue #4: Failed to open file csv2xls (on Mac OSX)
                parcecmd.cpp: Don't initialize optind=0
                The system does that, but with value '1'. (see: man 3 getopt)
                So value '0' was wrong.
                Since we don't parse argv twice or more, there is no reason, to touch it.
    * fix:      memory leaks
    * build:    make use of config.h

### Version: 0.3.2
    * build: remove automake as dependency
    * build: native on Windows (MinGW) works now

### Version: 0.3.1

    * allow directory as output path
    * Issue #3: write output files into current working directory

### Version: 0.3

    * options: added option -v to show program version
    * fixed issue #1:  make build target 'testing' optional
    * fixed issue #2: [parse command line] Dont print help twice

### Version: 0.2

    * removed boost as dependency
    * Don't allow less than 2 lines in xls file
      - If parameter '-H' is set and -l1 and csv input file has at least 2 lines,
        we end up in endless numbers of xls files with just the head line.

### Version: 0.1

    * added option '-D' to set digit count for file numbering
      - leading zeros help to sort output files by name
      
    * check command line parameters
      - max 10 digits for xls file numbering
      - max 65536 lines for one xls file
      - ignore columns > 256 in xls file
      - max 4GB for input buffer
      
    * crosscompiling
      - added mingwbuild.sh to make mingw builds easier

Date:    Mon 15. Oct 14:53:09 CET 2012

    initial commit

