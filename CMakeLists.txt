cmake_minimum_required(VERSION 3.12)
project(cpp_voxel_engine)

set(CMAKE_CXX_STANDARD 17)

set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp)

configure_file(src/Graphics/shaders/fShader.glsl ${PROJECT_SOURCE_DIR}/Graphics/shaders/fShader.glsl COPYONLY)
configure_file(src/Graphics/shaders/vShader.glsl ${PROJECT_SOURCE_DIR}/Graphics/shaders/vShader.glsl COPYONLY)
configure_file(src/Graphics/textures/textureAtlas.png ${PROJECT_SOURCE_DIR}/Graphics/textures/textureAtlas.png COPYONLY)

find_package(SFML COMPONENTS window REQUIRED)
find_package(OpenGL REQUIRED)

add_library(FastNoise SHARED "./lib/FastNoise/FastNoise.cpp")
add_library(glad SHARED "./lib/glad/src/glad.c")
link_libraries(dl)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(cpp_voxel_engine sfml-window glad GL FastNoise)