cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
include(FetchContent)
include(CppResultType)
set(EXTERN_CPPFUNCOMP_DIR ${EXTERN_DEPENDENCIES_DIR}/cppfuncomp)

FetchContent_Declare(
  cppfuncomp
  GIT_REPOSITORY https://github.com/ferkulat/CppFunComp.git
  GIT_TAG        28d837b43df9b1813333f3b959f8a987695df4eb
  SOURCE_DIR     ${EXTERN_CPPFUNCOMP_DIR}
)
if(NOT cppfuncomp_POPULATED)
    FetchContent_Populate(cppfuncomp)
endif()
include_directories(SYSTEM ${cppfuncomp_SOURCE_DIR}/include )

