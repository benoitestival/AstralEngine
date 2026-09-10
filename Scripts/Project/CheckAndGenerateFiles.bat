@echo off

setlocal ENABLEDELAYEDEXPANSION
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"

set "PROJECT_DIR=%~dp0..\.."
pushd "%PROJECT_DIR%"
set "PROJECT_DIR=%CD%"
popd

echo %ESC%[34m[INFO] Find project directory : %PROJECT_DIR%%ESC%[0m

for %%i in ("%PROJECT_DIR%") do set "PROJECT_NAME=%%~ni"

echo %ESC%[34m[INFO] Project name : %PROJECT_NAME%%ESC%[0m

if exist "%PROJECT_DIR%\vcpkg.json" (
    echo %ESC%[32m[OK] vcpkg.json found%ESC%[0m
) else (
	call "%~dp0CreateVcpkgJson.bat" "%PROJECT_DIR%" "%PROJECT_NAME%"
)

if exist "%PROJECT_DIR%\CMakePresets.json" (
    echo %ESC%[32m[OK] CMakePresets.json found%ESC%[0m
) else (
	call "%~dp0CreateCMakePresetJson.bat" "%PROJECT_DIR%"
)

if exist "%PROJECT_DIR%\CMakeLists.txt" (
    echo %ESC%[32m[OK] CMakeLists.txt already exists%ESC%[0m
) else (
	call "%~dp0CreateCmakeLists.bat" "%PROJECT_DIR%" "%PROJECT_NAME%"
)

echo.
echo %ESC%[32m[INFO] All project files are ready!%ESC%[0m
echo %ESC%[34m[INFO] Edit vcpkg.json to add your dependencies%ESC%[0m
echo %ESC%[34m[INFO] Edit CMakeLists.txt to add your sources and link libraries%ESC%[0m

endlocal
exit /b 0
