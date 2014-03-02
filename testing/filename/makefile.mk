filenameTestMain_SOURCES = \
			../src/filename.hpp ../src/filename.cpp \
		   	filename/filenameTest.hpp filename/filenameTest.cpp \
			filename/filenameTestMain.cpp filename/filenameTestMain.h
filenameTestMain_CXXFLAGS=$(CPPUFLAGS)
filenameTestMain_LDFLAGS=
filenameTestMain_LDADD=-L${libdir} -lCppUTest
filenameTestMain_CFLAGS = @CHECK_CFLAGS@

