@echo off

setlocal ENABLEDELAYEDEXPANSION

set "VCPKG_EXE="
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"

echo %ESC%[32m[INFO] Trying to find Vcpkg%ESC%[0m

echo %ESC%[34m[INFO] Looking through Path to find vcpkg%ESC%[0m
where vcpkg.exe >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    for /F "delims=" %%i in ('where vcpkg.exe') do (
        set "VCPKG_EXE=%%i"
        echo %ESC%[32m[INFO] Find in PATH%ESC%[0m
        goto FOUND
    )
)
echo %ESC%[33m[WARN] Vcpkg not found in Path%ESC%[0m
echo %ESC%[34m[INFO] Looking through common variable%ESC%[0m
for %%V in (VCPKG_ROOT VCPKG_ROOT_DIR VCPKG_HOME VCPKG_PATH VCPKG_DIR) do (
    if defined %%V (
        call set "CANDIDATE=%%%%V%%"
        if exist "!CANDIDATE!" (
            echo !CANDIDATE! | findstr /I /C:".exe" >nul && (
                set "VCPKG_EXE=!CANDIDATE!"
                echo %ESC%[32m[INFO] Vcpkg find in variable %%V%ESC%[0m
                goto FOUND
            )
        )
        if exist "!CANDIDATE!\vcpkg.exe" (
            set "VCPKG_EXE=!CANDIDATE!\vcpkg.exe"
            echo %ESC%[32m[INFO] Vcpkg find in variable %%V%ESC%[0m
            goto FOUND
        )
    )
)

goto END

:FOUND
endlocal & set "VCPKG_EXE=%VCPKG_EXE%"
exit /b 0

:END
endlocal
exit /b 1