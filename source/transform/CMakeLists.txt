set(PRIVATE_SOURCE
    hellotransform.cpp
)

add_executable(hellotransform ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(hellotransform GLFW OPENGL_UTILS)