@echo off

setlocal ENABLEDELAYEDEXPANSION
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"

set "PROJECT_DIR=%CD%"

:CHOICE
echo %ESC%[32m[CHOICE] Choose one of the option below: %ESC%[0m

echo %ESC%[35m[CHOICE] 1- You want to regenerate your solution %ESC%[0m
echo %ESC%[35m[CHOICE] 2- You want to setup or update the solution environment %ESC%[0m
echo %ESC%[35m[CHOICE] 3- Exit %ESC%[0m
CHOICE /C 123 /N /M "%ESC%[35mYour choice (1, 2 or 3): %ESC%[0m"
if errorlevel 3 goto EXIT
if errorlevel 2 goto SETUP_SOLUTION
if errorlevel 1 goto GENERATE_SOLUTION


:GENERATE_SOLUTION
set "MISSING=0"
if not exist "%PROJECT_DIR%\vcpkg.json" set "MISSING=1"
if not exist "%PROJECT_DIR%\CMakePresets.json" set "MISSING=1"
if not exist "%PROJECT_DIR%\CMakeLists.txt" set "MISSING=1"

if "%MISSING%"=="0" (
    where cmake >nul 2>nul
    if errorlevel 1 (
        echo %ESC%[31m[ERR] CMake est introuvable dans le PATH.%ESC%[0m
        echo %ESC%[33m[INFO] Installez CMake ^(https://cmake.org/download^).%ESC%[0m
        exit /b 1
    )
    if not exist "%PROJECT_DIR%\out\binaries" (
        mkdir "%PROJECT_DIR%\out\binaries"
    )
    pushd "%PROJECT_DIR%\out\binaries"
    cmake "%PROJECT_DIR%"
	cmake --build .
	popd
	goto CHOICE
) else (
    echo %ESC%[31m[ERR] No project setup for generating a solution%ESC%[0m
	goto CHOICE
)

:SETUP_SOLUTION
set "SETUP_PATH=%PROJECT_DIR%\Scripts\Setup.bat"
call "%SETUP_PATH%"
goto CHOICE

:EXIT
endlocal 
exit /b 0