@echo off

setlocal ENABLEDELAYEDEXPANSION
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"

echo %ESC%[34m[INFO] Updating vcpkg...%ESC%[0m
cd "%VCPKG_ROOT%"
git pull
call bootstrap-vcpkg.bat

endlocal
exit /b 0