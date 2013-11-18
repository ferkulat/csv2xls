str2ulongTestMain_SOURCES = \
				../src/str2ulong.cpp ../src/str2ulong.hpp \
				str2ulong/str2ulongTest.cpp str2ulong/str2ulongTestMain.cpp str2ulong/str2ulongTestMain.h
str2ulongTestMain_CXXFLAGS=$(CPPUTESTFLAGS)
str2ulongTestMain_LDFLAGS=
str2ulongTestMain_LDADD=-L${libdir} -lCppUTest
str2ulongTestMain_CFLAGS = @CHECK_CFLAGS@

