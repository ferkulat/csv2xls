add_library(csv2xlslib
        callback.cpp
        callback.hpp
        csv.cpp
        csv.hpp
        default_values.h
        filename.cpp
        filename.hpp
        parsecmd.cpp
        parsecmd.hpp
        parseCsvFile.cpp
        parseCsvFile.hpp
        readHeadLine.cpp
        readHeadLine.hpp
        XlsFile.cpp
        XlsFile.hpp
        xls_workbook.cpp
        xls_workbook.hpp
        callback.hpp
        conversion.h
        version.h
        OutPutDoc.hpp
        OutPutDoc.cpp
        csv2xls_types.cpp)
target_compile_options( csv2xlslib PUBLIC ${WARNINGOPTS} )
target_include_directories(csv2xlslib SYSTEM PRIVATE ${CMAKE_PREFIX_PATH}/include/xlslib)
message("CMAKE_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID}" )
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_link_libraries(csv2xlslib xlslib csv -static)
elseif(I_USE_MINGW)
    target_link_libraries(csv2xlslib xlslib csv iconv -static)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_link_libraries(csv2xlslib xlslib csv stdc++fs -static)
endif()
