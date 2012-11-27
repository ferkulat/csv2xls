bin_PROGRAMS = csv2xls

csv2xls_SOURCES = csv2xls.cpp  \
		  parsecmd.hpp parsecmd.cpp \
		  filename.hpp filename.cpp \
		  XlsFile.hpp XlsFile.cpp \
		  csv.hpp csv.cpp \
		  memory.hpp memory.cpp \
		  str2ulong.hpp str2ulong.cpp \
		  callback.hpp callback.cpp \
		  version.h

## depending on your configuration, you will have to uncomment
## the next line to cross compile with mingw
#csv2xls_LDFLAGS = -static

csv2xls_LDADD = -lxls -lcsv
csv2xls_CPPFLAGS = -Wall -g  -Werror -I${includedir}/xlslib

