set(PRIVATE_SOURCE
    hellotexture.cpp
)

add_executable(hellotexture ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(hellotexture GLFW OpenGL::GL OPENGL_UTILS)