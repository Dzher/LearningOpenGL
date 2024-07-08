set(PRIVATE_SOURCE
    lighting.cpp
    lighting.h
    main.cpp
)

add_executable(lighting ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(lighting GLFW OPENGL_UTILS)