cmake_minimum_required(VERSION 3.14)
find_package(Git)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
include( MunkeiVersionFromGit )

version_from_git(
  LOG       ON
  TIMESTAMP "%Y%m%d%H%M%S"
)

project(csv2xls VERSION ${VERSION} LANGUAGES CXX)

set(EXTERN_DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)

include(msvc_cplusplus)
include(doctest)
include(CTestConfig)
include(CTest)
include(warnings)
include(checkedcmd)
include(libcsv)
include(xlslib)

enable_testing()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/version.cpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")



include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/csv2xlslib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(doc)
add_subdirectory(csv2xlslib)
add_subdirectory(csv2xlslib.Test )
add_executable(csv2xls csv2xls.cpp ${version_file})
target_compile_options( csv2xls PUBLIC ${WARNINGOPTS} )
target_link_libraries(csv2xls csv2xlslib )

install(TARGETS csv2xls DESTINATION bin)
