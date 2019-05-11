if "%CONFIGURATION%"=="Debug" (
  ctest -j 2 -C %CONFIGURATION%
)
if "%CONFIGURATION%"=="Release" (
  ctest -j 2 -C %CONFIGURATION%
)