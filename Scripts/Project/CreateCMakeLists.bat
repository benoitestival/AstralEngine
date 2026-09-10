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

echo %ESC%[34m[INFO] Creating CMakeLists.txt...%ESC%[0m
(
	echo cmake_minimum_required(VERSION 3.20^)
	echo.
	echo set(CMAKE_CXX_STANDARD 17^)
	echo set(CMAKE_CXX_STANDARD_REQUIRED ON^)
	echo set_property(GLOBAL PROPERTY USE_FOLDERS ON^)
	echo.
	echo project(%PROJECT_NAME% VERSION 1.0.0 LANGUAGES CXX^)
	echo.
	echo # ============================================
	echo # Add your vcpkg packages here with find_package
	echo # Example:
	echo #   find_package(OpenGL REQUIRED^)
	echo #   find_package(glfw3 CONFIG REQUIRED^)
	echo #   find_package(GLEW CONFIG REQUIRED^)
	echo # ============================================
	echo.
	echo file(GLOB_RECURSE SOURCE_FILES ^${PROJECT_SOURCE_DIR}/Source/*.cpp^)
	echo file(GLOB_RECURSE HEADER_FILES ^${PROJECT_SOURCE_DIR}/Source/*.h^)
	echo file(GLOB_RECURSE INL_FILES ^${PROJECT_SOURCE_DIR}/Source/*.inl^)
	echo.
	echo list(APPEND HEADER_FILES ^${INL_FILES}^)
	echo.
	echo add_executable(^${PROJECT_NAME} ^${SOURCE_FILES} ^${HEADER_FILES}^)
	echo.
	echo set_source_files_properties(^${INL_FILES} PROPERTIES HEADER_FILE_ONLY TRUE^)
	echo # ============================================
	echo # Link your libraries here
	echo # Example:
	echo #   target_link_libraries(^${PROJECT_NAME} OpenGL::GL glfw GLEW::GLEW^)
	echo # ============================================
) > "%PROJECT_DIR%\CMakeLists.txt"
echo %ESC%[32m[OK] CMakeLists.txt created%ESC%[0m

endlocal
exit /b 0