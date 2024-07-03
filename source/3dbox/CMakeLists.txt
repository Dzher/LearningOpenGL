set(PRIVATE_SOURCE
    3dbox.cpp
)

add_executable(3dbox ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(3dbox GLFW OPENGL_UTILS)