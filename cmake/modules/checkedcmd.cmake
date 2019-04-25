cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  checked_cmd
  GIT_REPOSITORY https://github.com/ferkulat/CheckedCmd.git
  GIT_TAG        master
  SOURCE_DIR     ${EXTERN_CHECKED_CMD_DIR}
)
FetchContent_MakeAvailable(checked_cmd)
include_directories(${checked_cmd_SOURCE_DIR}/include )
