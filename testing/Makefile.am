
# MyProject C++: an example project using TDD

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
CPPUFLAGS = -Wall -Werror -I${includedir} -I${includedir}/CppUTest
TESTSCRIPTS = XlsFile/XlsFileTestMain.sh \
	Dummy/DummyTestMain.sh \
	filename/filenameTestMain.sh \
	parsecmd/parsecmdTestMain.sh
EXTRA_DIST = $(TESTSCRIPTS) testfunction.sh mkTest.sh
TESTS = $(TESTSCRIPTS)
noinst_PROGRAMS = XlsFileTestMain DummyTestMain filenameTestMain parsecmdTestMain
check_PROGRAMMS = XlsFileTestMain DummyTestMain filenameTestMain parsecmdTestMain

include XlsFile/makefile.mk
include Dummy/makefile.mk
include filename/makefile.mk
include parsecmd/makefile.mk



