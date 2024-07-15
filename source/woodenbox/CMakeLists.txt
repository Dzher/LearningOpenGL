set(PRIVATE_SOURCE
    woodenbox.cpp
    woodenbox.h
    main.cpp
)

add_executable(woodenbox ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(woodenbox GLFW OPENGL_UTILS)