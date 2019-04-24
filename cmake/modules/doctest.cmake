cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

include(FetchContent)

set(EXTERN_DOCTEST_TAG 2.3.1)
set(DOCTEST_PROJECT_NAME extern_doctest)

FetchContent_Declare(
  ${DOCTEST_PROJECT_NAME}
  DOWNLOAD_NO_EXTRACT true
  DOWNLOAD URL        https://raw.githubusercontent.com/onqtam/doctest/${EXTERN_DOCTEST_TAG}/doctest/doctest.h
  DOWNLOAD_DIR        ${EXTERN_DOCTEST_HEADER_DIR}
)

FetchContent_GetProperties(${DOCTEST_PROJECT_NAME})
if(NOT ${DOCTEST_PROJECT_NAME}_POPULATED)
  FetchContent_Populate(${DOCTEST_PROJECT_NAME})
endif()
include_directories(${EXTERN_DOCTEST_HEADER_DIR})