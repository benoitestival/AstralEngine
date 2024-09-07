cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Configure Vcpkg
find_program(VCPKG_EXECUTABLE vcpkg)#find in PATH a vcpkg variable
get_filename_component(VCPKG_ROOT ${VCPKG_EXECUTABLE} DIRECTORY)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
include(${CMAKE_TOOLCHAIN_FILE})

project(AstralEngine CXX)#project definition + check and initialization of all settings and compilateur suffs


find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)

find_package(SFML CONFIG REQUIRED COMPONENTS graphics audio system window)

find_package(jsoncpp CONFIG REQUIRED)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/Source/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${PROJECT_SOURCE_DIR}/Source/*.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-system sfml-window)

target_link_libraries(${PROJECT_NAME} JsonCpp::JsonCpp)

