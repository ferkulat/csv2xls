cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
include(FetchContent)

set(EXTERN_CPPSKILLEDTYPE_DIR ${EXTERN_DEPENDENCIES_DIR}/cppskilledtype)

FetchContent_Declare(
  cppskilledtype
  GIT_REPOSITORY https://github.com/ferkulat/CppSkilledType.git
  GIT_TAG        c315e6ec1d8397db6b40a28361f0f20e7aa86635
  SOURCE_DIR     ${EXTERN_CPPSKILLEDTYPE_DIR}
)
if(NOT cppskilledtype_POPULATED)
    FetchContent_Populate(cppskilledtype)
endif()
include_directories(SYSTEM ${cppskilledtype_SOURCE_DIR}/include )

