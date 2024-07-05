set(PRIVATE_SOURCE
    hellotriangle.cpp
)

add_executable(hellotriangle ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(hellotriangle GLFW)