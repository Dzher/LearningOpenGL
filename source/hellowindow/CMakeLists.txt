set(PRIVATE_SOURCE
    hellowindow.cpp
)

add_executable(hellowindow ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(hellowindow GLFW OpenGL::GL)