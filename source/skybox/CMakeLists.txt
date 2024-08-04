set(PRIVATE_SOURCE
    skybox.cpp
    skybox.h
    main.cpp
)

add_executable(skybox ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(skybox GLFW OPENGL_UTILS)