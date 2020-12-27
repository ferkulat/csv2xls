cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
include(FetchContent)

FetchContent_Declare(
  checked_cmd
  GIT_REPOSITORY https://github.com/ferkulat/CheckedCmd.git
  GIT_TAG        d314fd381168d8528761f051c33f3157576e5324
)
FetchContent_MakeAvailable(checked_cmd)
