add_library(OPENGL_UTILS STATIC)

set(PRIVATE_SOURCE
    shader.cpp
    shader.h
)

target_sources(OPENGL_UTILS
    PRIVATE
    ${PRIVATE_SOURCE}
)

target_include_directories(OPENGL_UTILS PUBLIC ${CMAKE_SOURCE_DIR}/source)