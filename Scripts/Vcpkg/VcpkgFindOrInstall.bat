@echo off

setlocal ENABLEDELAYEDEXPANSION

set "VCPKG_DIR="

for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"

:CHOICE
echo %ESC%[33m[WARN] Vcpkg not found in your environnement variables, choose one of the two next options: %ESC%[0m

echo %ESC%[35m[CHOICE] 1- You havent Vcpkg on your computer and need to install it %ESC%[0m
echo %ESC%[35m[CHOICE] 2- You have Vcpkg on your computer but it is not in environnement variables %ESC%[0m

CHOICE /C 12 /N /M "%ESC%[35mYour choice (1 or 2): %ESC%[0m"
if errorlevel 2 goto FIND_EXISTING
if errorlevel 1 goto INSTALL

:INSTALL
for /f "delims=" %%i in ('powershell -NoProfile -Command "[Environment]::GetFolderPath('MyDocuments')"') do set "DOCS=%%i"
set "DEFAULT_DIR=%DOCS%\Vcpkg"

where git >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo %ESC%[31m[ERR] Git is not installed%ESC%[0m
    exit /b 1
)

echo %ESC%[35m[CHOICE] 1- Do you want to install vcpkg in a custom folder ? %ESC%[0m
echo %ESC%[35m[CHOICE] 2- Do you want to install vcpkg in the default folder (Documents) ? %ESC%[0m
CHOICE /C 12 /N /M "%ESC%[35mYour choice (1 or 2): %ESC%[0m"
if errorlevel 2 goto DEFAULTVCPKGINSTALL
if errorlevel 1 goto CUSTOMVCPKGINSTALL

:CUSTOMVCPKGINSTALL
echo %ESC%[35m[CHOICE] Define Vcpkg desired path.%ESC%[0m
set "USER_DIR="
set /p "USER_DIR=%ESC%[35mChemin: %ESC%[0m"
set "USER_DIR=!USER_DIR:"=!"

if not defined USER_DIR (
    echo %ESC%[31m[ERR] Aucun chemin saisi.%ESC%[0m
    goto CUSTOMVCPKGINSTALL
)

if "!USER_DIR:~-1!"=="\" set "USER_DIR=!USER_DIR:~0,-1!"

set "VCPKG_DIR=!USER_DIR!"
echo %ESC%[34m[INFO] Installation dans : !VCPKG_DIR!%ESC%[0m
echo %ESC%[35m[CHOICE] Is this path okay ? 1-Yes 2-No %ESC%[0m
CHOICE /C 12 /N /M "%ESC%[35mYour choice (1 or 2): %ESC%[0m"
if errorlevel 2 goto INSTALL
if errorlevel 1 goto VCPKGINSTALL

:DEFAULTVCPKGINSTALL
set "VCPKG_DIR=%DOCS%\Vcpkg"
if not exist "%VCPKG_DIR%" (
	mkdir "%VCPKG_DIR%"
)
goto VCPKGINSTALL

:VCPKGINSTALL
echo %ESC%[34m[INFO] Clonage de vcpkg...%ESC%[0m
git clone https://github.com/Microsoft/vcpkg.git "%VCPKG_DIR%"
if !ERRORLEVEL! NEQ 0 (
    echo %ESC%[31m[ERR] Echec du clonage ^(dossier deja non vide ?^)%ESC%[0m
    exit /b 1
)
pushd "%VCPKG_DIR%"
call bootstrap-vcpkg.bat
set "BOOT_ERR=!ERRORLEVEL!"
popd
if !BOOT_ERR! NEQ 0 (
    echo %ESC%[31m[ERR] Echec du bootstrap.%ESC%[0m
    exit /b 1
)
echo %ESC%[32m[INFO] Vcpkg installed successfully%ESC%[0m
endlocal & set "VCPKG_EXE=%VCPKG_DIR%\vcpkg.exe"
exit /b 0

:FIND_EXISTING
set /p VCPKG_DIR="%ESC%[35mEntrez le chemin jusqu'a Vcpkg sur votre disque: %ESC%[0m"
if exist "!VCPKG_DIR!\vcpkg.exe" (
	set "VCPKG_EXE=!VCPKG_DIR!\vcpkg.exe"
) else if exist "!VCPKG_DIR!" (
	echo !VCPKG_DIR! | findstr /I /C:".exe" >nul && (
        set "VCPKG_EXE=!VCPKG_DIR!"
    ) || (
        echo %ESC%[31m[ERR] vcpkg.exe introuvable dans ce dossier%ESC%[0m
		goto CHOICE
    )
)
endlocal & set "VCPKG_EXE=%VCPKG_EXE%"
exit /b 0