@echo off
setlocal ENABLEDELAYEDEXPANSION
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"

set "PROJECT_DIR=%~1"
if "%PROJECT_DIR%"=="" (
    echo %ESC%[31m[ERR] No project directory provided%ESC%[0m
    exit /b 1
)

echo %ESC%[34m[INFO] Creating CMakePresets.json...%ESC%[0m
(
	echo {
	echo   "version": 3,
	echo   "configurePresets": [
	echo     {
	echo       "name": "Default",
	echo       "displayName": "Default",
	echo       "binaryDir": "${sourceDir}/build",
	echo       "cacheVariables": {
	echo         "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
	echo       }
	echo     },
	echo     {
	echo       "name": "Debug",
	echo       "displayName": "Debug",
	echo       "inherits": "Default",
	echo       "cacheVariables": {
	echo         "CMAKE_BUILD_TYPE": "Debug"
	echo       }
	echo     },
	echo     {
	echo       "name": "Release",
	echo       "displayName": "Release",
	echo       "inherits": "Default",
	echo       "cacheVariables": {
	echo         "CMAKE_BUILD_TYPE": "Release"
	echo       }
	echo     }
	echo   ],
	echo   "buildPresets": [
	echo     {
	echo       "name": "Default",
	echo       "configurePreset": "Default"
	echo     },
	echo     {
	echo       "name": "Debug",
	echo       "configurePreset": "Debug"
	echo     },
	echo     {
	echo       "name": "Release",
	echo       "configurePreset": "Release"
	echo     }
	echo   ]
	echo }
) > "%PROJECT_DIR%\CMakePresets.json"
echo %ESC%[32m[OK] CMakePresets.json created%ESC%[0m

endlocal
exit /b 0