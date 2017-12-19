set(TEST_SOURCE_FILES
        csv2xlslibTest.cpp
        doctest.h
        filenameTest.cpp
        parsecmdTest.cpp
        XlsFileTest.cpp
        conversionTest.cpp)
add_executable(csv2xlslibTest ${TEST_SOURCE_FILES} ${version_file})
target_link_libraries(csv2xlslibTest csv2xlslib)
