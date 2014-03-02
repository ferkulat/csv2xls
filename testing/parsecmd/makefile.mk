parsecmdTestMain_SOURCES =	parsecmd/parsecmdTest.cpp parsecmd/parsecmdTestMain.cpp parsecmd/parsecmdTestMain.h\
		   	../src/parsecmd.hpp ../src/parsecmd.cpp \
			../src/filename.hpp ../src/filename.cpp
parsecmdTestMain_CXXFLAGS=$(CPPUTESTFLAGS)
parsecmdTestMain_LDFLAGS=
parsecmdTestMain_LDADD=-L${libdir} -lCppUTest
parsecmdTestMain_CFLAGS = @CHECK_CFLAGS@

