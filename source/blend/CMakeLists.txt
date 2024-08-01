set(PRIVATE_SOURCE
    blend.cpp
    blend.h
    main.cpp
)

add_executable(blend ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(blend GLFW OPENGL_UTILS)