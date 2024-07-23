add_library(OPENGL_UTILS STATIC)

set(PRIVATE_SOURCE
    shader/shader.cpp
    shader/shader.h
    pathhelper/pathhelper.cpp
    pathhelper/pathhelper.h
    common/common.cpp
    common/common.h
    camera/camera.cpp
    camera/camera.h
    material/material.cpp
    material/material.h
    mesh/mesh.cpp
    mesh/mesh.h
    model/model.cpp
    model/model.h
)

target_sources(OPENGL_UTILS
    PRIVATE
    ${PRIVATE_SOURCE}
)

# target_link_libraries(OPENGL_UTILS PUBLIC assimp::assimp)
target_include_directories(OPENGL_UTILS PUBLIC ${CMAKE_SOURCE_DIR}/source)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.in ${CMAKE_SOURCE_DIR}/include/config.h @ONLY)