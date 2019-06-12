add_library(csv2xlslib
        callback.cpp
        callback.hpp
        csv.cpp
        csv.hpp
        default_values.h
        parsecmd.cpp
        parsecmd.hpp
        parseCsvFile.cpp
        parseCsvFile.hpp
        readHeadLine.cpp
        readHeadLine.hpp
        XlsFile.cpp
        XlsFile.hpp
        XlsWorkBook.cpp
        XlsWorkBook.hpp
        callback.hpp
        conversion.h
        version.h
        OutputDoc.hpp
        OutputDoc.cpp
        csv2xls_compound_types.h
        csv2xls_compound_types.cpp
        csv2xls_skills.h
        MatchVariantType.h
        readBuffer.h
        readBuffer.cpp
        convertCsv.cpp convertCsv.h funcomp.h)
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
