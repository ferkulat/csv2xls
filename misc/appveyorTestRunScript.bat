if "%CONFIGURATION%"=="Debug" (
  ctest --exclude-regex "CheckedCmdTests|check_csv" -j 2 -C %CONFIGURATION%
)
if "%CONFIGURATION%"=="Release" (
  ctest --exclude-regex "CheckedCmdTests|check_csv" -j 2 -C %CONFIGURATION%
)