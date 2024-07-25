set(PRIVATE_SOURCE
    stenciltest.cpp
    stenciltest.h
    main.cpp
)

add_executable(stenciltest ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(stenciltest GLFW OPENGL_UTILS)