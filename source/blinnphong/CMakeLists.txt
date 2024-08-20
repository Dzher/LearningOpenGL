set(PRIVATE_SOURCE
    blinnphong.cpp
    blinnphong.h
    main.cpp
)

add_executable(blinnphong ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(blinnphong GLFW OPENGL_UTILS)