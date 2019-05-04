cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
include(FetchContent)
set(EXTERN_XLSLIB_DIR ${EXTERN_DEPENDENCIES_DIR}/xlslib)

FetchContent_Declare(
  xlslib
  GIT_REPOSITORY https://github.com/ferkulat/xlslib.git
  GIT_TAG        227776845cca16a50213359c58c7b9e8264520d9
  SOURCE_DIR     ${EXTERN_XLSLIB_DIR}
)
FetchContent_MakeAvailable(xlslib)
include_directories(SYSTEM ${xlslib_SOURCE_DIR}/xlslib/src )
include_directories(SYSTEM ${xlslib_SOURCE_DIR} )
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    include_directories(SYSTEM ${xlslib_SOURCE_DIR}/xlslib/build/msvc2019 )
endif()

add_subdirectory(${xlslib_SOURCE_DIR}/xlslib)
