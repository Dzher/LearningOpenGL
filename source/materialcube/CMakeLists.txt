set(PRIVATE_SOURCE
    materialcube.cpp
    materialcube.h
    main.cpp
)

add_executable(materialcube ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(materialcube GLFW OPENGL_UTILS)