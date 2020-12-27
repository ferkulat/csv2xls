cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
set(EXTERN_CLARA_TAG v1.1.5)
set(EXTERN_CLARA_HEADER_DIR ${EXTERN_DEPENDENCIES_DIR}/clara)

include(FetchContent)
# ------------------------------------------------------------------------------
# A modern, C++-native, header-only, test framework for unit-tests,
# TDD and BDD - using C++11, C++14, C++17 and later
FetchContent_Declare( extern_clara
      GIT_REPOSITORY  https://github.com/catchorg/Clara.git
      GIT_TAG         v1.1.5
)

FetchContent_GetProperties(extern_clara)
if(NOT extern_clara_POPULATED)
    FetchContent_Populate(extern_clara)
#    add_subdirectory(${extern_clara_SOURCE_DIR} ${extern_clara_BINARY_DIR})
endif()

add_library(clara INTERFACE)
target_include_directories(clara INTERFACE
        $<BUILD_INTERFACE:${extern_clara_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
