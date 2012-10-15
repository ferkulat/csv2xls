bin_PROGRAMS = csv2xls

csv2xls_SOURCES = csv2xls.cpp  \
		  parsecmd.hpp parsecmd.cpp \
		  filename.hpp filename.cpp \
		  XlsFile.hpp XlsFile.cpp \
		  csv.hpp csv.cpp \
		  memory.hpp memory.cpp 
#csv2xls_LDFLAGS = -static
csv2xls_LDADD = -lxls -lcsv  
csv2xls_CPPFLAGS = -Wall -g  -Werror -I${includedir}/xlslib

