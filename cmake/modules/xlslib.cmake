cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
include(FetchContent)
set(EXTERN_XLSLIB_DIR ${EXTERN_DEPENDENCIES_DIR}/xlslib)

FetchContent_Declare(
  xlslib
  GIT_REPOSITORY https://github.com/ferkulat/xlslib.git
  GIT_TAG        28fb458bc5ba2da614f4738d9560a6fb917d49a9
  SOURCE_DIR     ${EXTERN_XLSLIB_DIR}
)
FetchContent_MakeAvailable(xlslib)
include_directories(SYSTEM ${xlslib_SOURCE_DIR}/xlslib/src )
include_directories(SYSTEM ${xlslib_SOURCE_DIR} )
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    include_directories(SYSTEM ${xlslib_SOURCE_DIR}/xlslib/build/msvc2019 )
endif()

add_subdirectory(${xlslib_SOURCE_DIR}/xlslib)
