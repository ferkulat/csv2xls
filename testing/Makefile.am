
# MyProject C++: an example project using TDD

AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
CPPUFLAGS = -Wall -Werror -I${includedir} -I${includedir}/CppUTest
TESTSCRIPTS = XlsFile/XlsFileTestMain.sh \
	Dummy/DummyTestMain.sh \
	filename/filenameTestMain.sh \
	str2ulong/str2ulongTestMain.sh \
	parsecmd/parsecmdTestMain.sh
EXTRA_DIST = $(TESTSCRIPTS) testfunction.sh mkTest.sh
TESTS = $(TESTSCRIPTS)
noinst_PROGRAMS = XlsFileTestMain DummyTestMain filenameTestMain str2ulongTestMain parsecmdTestMain
check_PROGRAMMS = XlsFileTestMain DummyTestMain filenameTestMain str2ulongTestMain parsecmdTestMain

include XlsFile/makefile.mk
include Dummy/makefile.mk
include filename/makefile.mk
include str2ulong/makefile.mk
include parsecmd/makefile.mk



