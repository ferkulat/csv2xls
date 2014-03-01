bin_PROGRAMS = csv2xls

csv2xls_SOURCES = csv2xls.cpp  \
		  parsecmd.hpp parsecmd.cpp \
		  filename.hpp filename.cpp \
		  XlsFile.hpp XlsFile.cpp \
		  csv.hpp csv.cpp \
		  memory.hpp memory.cpp \
		  str2ulong.hpp str2ulong.cpp \
		  callback.hpp callback.cpp \
		  xlslib.hpp \
		  workbook.hpp xls_workbook.hpp xls_workbook.cpp \
		  readHeadLine.hpp readHeadLine.cpp \
		  parseCsvFile.hpp parseCsvFile.cpp \
		  print_help.h print_help.cpp \
		  default_values.h

## depending on your configuration, you will have to uncomment
## the next line to cross compile with mingw
#csv2xls_LDFLAGS = -static

csv2xls_LDADD = -L${libdir} -lxls -lcsv
csv2xls_CPPFLAGS = -Wall -Werror -I${includedir}/xlslib -I${includedir}

