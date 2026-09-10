@echo off
setlocal ENABLEDELAYEDEXPANSION
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"

set "PROJECT_DIR=%~1"
set "PROJECT_NAME=%~2"
if "%PROJECT_DIR%"=="" (
    echo %ESC%[31m[ERR] No project directory provided%ESC%[0m
    exit /b 1
)
if "%PROJECT_NAME%"=="" (
    echo %ESC%[31m[ERR] No project name provided%ESC%[0m
    exit /b 1
)

echo %ESC%[34m[INFO] Creating vcpkg.json...%ESC%[0m
(
	echo {
	echo   "name": "%PROJECT_NAME%",
	echo   "version-string": "1.0.0",
	echo   "dependencies": [
	echo   ]
	echo }
) > "%PROJECT_DIR%\vcpkg.json"
echo %ESC%[32m[OK] vcpkg.json created%ESC%[0m

endlocal
exit /b 0