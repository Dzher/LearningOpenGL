add_library(OPENGL_UTILS STATIC)

set(PRIVATE_SOURCE
    shader/shader.cpp
    shader/shader.h
    pathhelper/pathhelper.cpp
    pathhelper/pathhelper.h
    common/common.cpp
    common/common.h
)

target_sources(OPENGL_UTILS
    PRIVATE
    ${PRIVATE_SOURCE}
)

target_include_directories(OPENGL_UTILS PUBLIC ${CMAKE_SOURCE_DIR}/source)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.in ${CMAKE_SOURCE_DIR}/include/config.h @ONLY)