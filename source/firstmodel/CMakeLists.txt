set(PRIVATE_SOURCE
    firstmodel.cpp
    firstmodel.h
    main.cpp
)

add_executable(firstmodel ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(firstmodel GLFW OPENGL_UTILS assimp::assimp)
