cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SFML "Build Engine with sfml" ON)

# Configure Vcpkg
find_program(VCPKG_EXECUTABLE vcpkg)#find in PATH a vcpkg variable
get_filename_component(VCPKG_ROOT ${VCPKG_EXECUTABLE} DIRECTORY)
include(CMakePrintHelpers)
cmake_print_variables(VCPKG_EXECUTABLE)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
include(${CMAKE_TOOLCHAIN_FILE})

project(Engine CXX)#project definition + check and initialization of all settings and compilateur suffs

if (BUILD_SFML)
	find_package(SFML CONFIG REQUIRED COMPONENTS graphics audio system window)
	
	#debug
	message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
	message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
endif()

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/Source/*.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if (BUILD_SFML)
	target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-system sfml-window)
endif()
