@echo off

setlocal ENABLEDELAYEDEXPANSION

set "SCRIPT_PATH=%~dp0"

rem research of vcpkg
call "%SCRIPT_PATH%\Vcpkg\VcpkgSearch.bat"

if %ERRORLEVEL% EQU 1 (
	call "%SCRIPT_PATH%\Vcpkg\VcpkgFindOrInstall.bat"
	if !ERRORLEVEL! NEQ 0 (
        echo [ERR] Installation de vcpkg echouee.
        exit /b 1
    )
)

if not defined VCPKG_EXE (
    echo [ERR] VCPKG_EXE non defini.
    exit /b 1
)

for %%i in ("!VCPKG_EXE!") do set "VCPKG_ROOT_DIR=%%~dpi"
set "VCPKG_ROOT=!VCPKG_ROOT_DIR!"
setx VCPKG_ROOT "!VCPKG_ROOT_DIR!"

call "%SCRIPT_PATH%\Vcpkg\VcpkgUpdate.bat"

call "%SCRIPT_PATH%\Project\CheckAndGenerateFiles.bat"

endlocal 
exit /b 0