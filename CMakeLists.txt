cmake_minimum_required(VERSION 3.21)
project(QtOpenGLTest)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
add_executable(hello helloworld.cpp)

# sub directories
add_subdirectory(helloqtopengl)
add_subdirectory(hellopureopengl)
