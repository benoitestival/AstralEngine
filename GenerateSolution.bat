set SOURCE_PATH=%CD%

mkdir out\binaries
cd out\binaries

cmake %SOURCE_PATH%
pause
cmake --build