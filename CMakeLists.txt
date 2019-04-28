cmake_minimum_required(VERSION 3.14)
find_package(Git)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
include( MunkeiVersionFromGit )

version_from_git(
  LOG       ON
  TIMESTAMP "%Y%m%d%H%M%S"
)

project(csv2xls VERSION ${VERSION} LANGUAGES CXX)

#if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
#set(VERSION_UPDATE_FROM_GIT "TRUE")
#else()
#set(VERSION_UPDATE_FROM_GIT "FALSE")
#endif()

#
# Make a version file containing the current version from git.
#
include(msvc_cplusplus)
set(EXTERN_DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern)
set(EXTERN_CHECKED_CMD_DIR ${EXTERN_DEPENDENCIES_DIR}/checked_cmd)
set(EXTERN_DOCTEST_HEADER_DIR ${EXTERN_DEPENDENCIES_DIR}/doctest)
set(EXTERN_LIBCSV_DIR ${EXTERN_DEPENDENCIES_DIR}/libcsv)
set(EXTERN_XLSLIB_DIR ${EXTERN_DEPENDENCIES_DIR}/xlslib)

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
include_directories(SYSTEM ${EXTERN_CHECKED_CMD_DIR}/extern/clara)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(doc)
add_subdirectory(csv2xlslib)
add_subdirectory(csv2xlslib.Test )
add_executable(csv2xls csv2xls.cpp ${version_file})
target_compile_options( csv2xls PUBLIC ${WARNINGOPTS} )
target_link_libraries(csv2xls csv2xlslib )

install(TARGETS csv2xls DESTINATION bin)
