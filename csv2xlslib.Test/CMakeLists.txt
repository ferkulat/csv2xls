
set(TEST_SOURCE_FILES
        csv2xlslibTest.cpp
        OutputFileNameTest.cpp
        parsecmdTest.cpp
        XlsFileTest.cpp
        conversionTest.cpp
        parseCsvStreamTest.cpp
        TestHelper.h
        ReadCellTest.cpp)
add_executable(csv2xlslibTest ${TEST_SOURCE_FILES} ${version_file})
target_link_libraries(csv2xlslibTest csv2xlslib)
add_test(
        NAME csv2xlslibTest
        COMMAND csv2xlslibTest
)
