
# MyProject C++: an example project using TDD

AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

TESTS = TestMain
noinst_PROGRAMS = TestMain

TestMain_SOURCES = ../src/filename.hpp ../src/filename.cpp \
			filenameTest.hpp filenameTest.cpp \
		   	../src/parsecmd.hpp ../src/parsecmd.cpp \
			parsecmdTest.hpp parsecmdTest.cpp \
			../src/str2ulong.hpp ../src/str2ulong.cpp \
			str2ulongTest.hpp str2ulongTest.cpp \
			TestMain.cpp
TestMain_CXXFLAGS=$(CPPUNIT_CFLAGS) -Wall -Werror -I${includedir}/xlslib
TestMain_LDFLAGS=$(CPPUNIT_LIBS)
TestMain_LDADD=-lcppunit -ldl -lxls
TestMain_CFLAGS = @CHECK_CFLAGS@
