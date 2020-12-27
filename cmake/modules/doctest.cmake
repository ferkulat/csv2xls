cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include(FetchContent)

FetchContent_Declare( extern_doctest
    GIT_REPOSITORY  https://github.com/onqtam/doctest.git
    GIT_TAG         2.4.4
)

FetchContent_MakeAvailable(extern_doctest)
