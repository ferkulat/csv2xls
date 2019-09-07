add_library(csv2xlslib
        default_values.h
        parsecmd.cpp
        parsecmd.hpp
        parseCsvFile.cpp
        parseCsvFile.hpp
        XlsWorkBook.cpp
        XlsWorkBook.hpp
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
        convertCsv.h
        funcomp.h
        Helpers.h
        convertCsv.cpp)
target_compile_options( csv2xlslib PUBLIC ${WARNINGOPTS} )
target_include_directories(csv2xlslib SYSTEM PRIVATE ${CMAKE_PREFIX_PATH}/include/xlslib)
message("CMAKE_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID}" )
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_link_libraries(csv2xlslib xlslib -static)
elseif(I_USE_MINGW)
    target_link_libraries(csv2xlslib xlslib iconv -static)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_link_libraries(csv2xlslib xlslib stdc++fs -static)
endif()
