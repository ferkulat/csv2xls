DummyTestMain_SOURCES =	Dummy/DummyTest.hpp Dummy/DummyTest.cpp Dummy/DummyTestMain.cpp Dummy/DummyTestMain.h
DummyTestMain_CXXFLAGS=$(CPPUTESTFLAGS)
DummyTestMain_LDFLAGS=
DummyTestMain_LDADD=-L${libdir} -lCppUTest
DummyTestMain_CFLAGS = @CHECK_CFLAGS@

