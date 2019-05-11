cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
include(FetchContent)
set(EXTERN_CHECKED_CMD_DIR ${EXTERN_DEPENDENCIES_DIR}/checked_cmd)

FetchContent_Declare(
  checked_cmd
  GIT_REPOSITORY https://github.com/ferkulat/CheckedCmd.git
  GIT_TAG        139af9879403ec1ea589e09bb19839ea309ade98
  SOURCE_DIR     ${EXTERN_CHECKED_CMD_DIR}
)
if(NOT checked_cmd_POPULATED)
    FetchContent_MakeAvailable(checked_cmd)
endif()
include_directories(${checked_cmd_SOURCE_DIR}/include )
include_directories(SYSTEM ${EXTERN_CHECKED_CMD_DIR}/extern/clara)
