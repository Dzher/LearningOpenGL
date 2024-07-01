add_library(OPENGL_UTILS STATIC)

set(OPENGL_UTILS_SRCS
    shader.cpp
    shader.h
)

target_sources(OPENGL_UTILS
    PRIVATE
    ${OPENGL_UTILS_SRCS}
)

target_include_directories(OPENGL_UTILS PUBLIC ${CMAKE_SOURCE_DIR}/source)