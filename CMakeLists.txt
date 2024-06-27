cmake_minimum_required(VERSION 3.21)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.c)

add_library(glfw STATIC IMPORTED)
# add_library(glfw SHARED IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libs/libglfw3.a)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(OpenGL REQUIRED)

# sub directories
add_subdirectory(source)
