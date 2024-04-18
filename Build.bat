set SOURCE_PATH=%CD%

mkdir out\binaries
cd out\binaries

cmake %SOURCE_PATH%
cmake --build