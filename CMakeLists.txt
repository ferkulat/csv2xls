cmake_minimum_required(VERSION 3.6)
find_package(Git)
project(csv2xls)
enable_testing()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
set(VERSION_UPDATE_FROM_GIT "TRUE")
else()
set(VERSION_UPDATE_FROM_GIT "FALSE")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
#
# Make a version file containing the current version from git.
#
include(GetVersionFromGitTag)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/version.cpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/version.cpp)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")



include_directories("${PROJECT_BINARY_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/csv2xlslib)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

if( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    set( WARNINGOPTS -Wall -Wextra -Wpedantic -Wimplicit-fallthrough -Warray-bounds -Wshadow -Wconversion -Wsign-conversion -Wparentheses -Werror )
endif()
if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    set( WARNINGOPTS  /W4 /WX )
endif()

add_subdirectory(doc)
add_subdirectory(csv2xlslib)
add_subdirectory(csv2xlslib.Test EXCLUDE_FROM_ALL)
add_executable(csv2xls csv2xls.cpp ${version_file})
target_compile_options( csv2xls PUBLIC ${WARNINGOPTS} )
target_link_libraries(csv2xls csv2xlslib xls csv)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

add_test( csv2xlslibTest  csv2xlslib.Test/csv2xlslibTest)
add_dependencies(check csv2xlslibTest)
install(TARGETS csv2xls DESTINATION bin)