cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  libcsv
  GIT_REPOSITORY https://github.com/ferkulat/libcsv.git
  GIT_TAG        3af9a53da5d64f14584e4bf69c3b7272cb97893d
  SOURCE_DIR     ${EXTERN_LIBCSV_DIR}
)
FetchContent_MakeAvailable(libcsv)
include_directories(${libcsv_SOURCE_DIR} )
