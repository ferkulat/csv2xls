cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

include(FetchContent)
set(EXTERN_CATCH_HEADER_DIR ${EXTERN_DEPENDENCIES_DIR}/catch)
set(EXTERN_CATCH_TAG v2.7.1)

# ------------------------------------------------------------------------------
# A modern, C++-native, header-only, test framework for unit-tests,
# TDD and BDD - using C++11, C++14, C++17 and later
FetchContent_Declare(
  extern_catch2
  DOWNLOAD_NO_EXTRACT true
  DOWNLOAD URL        https://github.com/catchorg/Catch2/releases/download/${EXTERN_CATCH_TAG}/catch.hpp
  DOWNLOAD_DIR        ${EXTERN_CATCH_HEADER_DIR}
)

FetchContent_GetProperties(extern_catch2)
if(NOT extern_catch2_POPULATED)
  FetchContent_Populate(extern_catch2)
endif()
include_directories(SYSTEM ${EXTERN_CATCH_HEADER_DIR})