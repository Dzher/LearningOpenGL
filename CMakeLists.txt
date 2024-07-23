cmake_minimum_required(VERSION 3.21)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.c)

add_library(GLFW STATIC IMPORTED)
set_target_properties(GLFW PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/libglfw3.a)
# add_library(ASSIMP STATIC IMPORTED)
# set_target_properties(ASSIMP PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/libassimp.dll.a)
find_package(assimp REQUIRED)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# sub directories
add_subdirectory(source)
