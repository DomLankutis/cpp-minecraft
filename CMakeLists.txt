cmake_minimum_required(VERSION 3.12)
project(cpp_minecraft)

set(CMAKE_CXX_STANDARD 17)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

file(GLOB_RECURSE cpp_minecraft_SOURCES src/*.cpp)
file(GLOB_RECURSE cpp_minecraft_HEADERS src/*.hpp)

find_package(SFML COMPONENTS window REQUIRED)
find_package(OpenGL REQUIRED)

add_library(FastNoise "./lib/FastNoise/FastNoise.cpp")
add_library(glad "./lib/glad/src/glad.c")
link_libraries(dl)

add_executable(${PROJECT_NAME} ${cpp_minecraft_SOURCES} ${cpp_minecract_HEADERS})
target_link_libraries(cpp_minecraft sfml-window glad GL FastNoise)