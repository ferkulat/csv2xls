XlsFileTestMain_SOURCES = XlsFile/XlsFileTest.hpp XlsFile/XlsFileTest.cpp XlsFile/XlsFileTestMain.cpp XlsFile/XlsFileTestMain.h \
			../src/filename.hpp ../src/filename.cpp \
			../src/XlsFile.hpp ../src/XlsFile.cpp 
XlsFileTestMain_CXXFLAGS=$(CPPUTESTFLAGS)
XlsFileTestMain_LDFLAGS=
XlsFileTestMain_LDADD=-L${libdir} -lCppUTest
XlsFileTestMain_CFLAGS = @CHECK_CFLAGS@

