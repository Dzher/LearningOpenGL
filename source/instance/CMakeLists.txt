set(PRIVATE_SOURCE
    instance.cpp
    instance.h
    main.cpp
)

add_executable(instance ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(instance GLFW OPENGL_UTILS assimp::assimp)