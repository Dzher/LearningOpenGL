set(PRIVATE_SOURCE
    helloshader.cpp
)

add_executable(helloshader ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(helloshader GLFW OpenGL::GL)