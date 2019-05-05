if( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    #https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
    #Clara checks for this value to enable support for std::optional
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus" )
endif()
