INCLUDE_DIRECTORIES(SYSTEM /usr/include/xlslib)
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
        print_help.cpp
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
        OutPutDoc.cpp)
target_compile_options( csv2xlslib PUBLIC ${WARNINGOPTS} )
target_link_libraries(csv2xlslib  xls csv)
