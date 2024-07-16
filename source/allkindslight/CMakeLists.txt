set(PRIVATE_SOURCE
    allkindslight.cpp
    allkindslight.h
    main.cpp
)

add_executable(allkindslight ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(allkindslight GLFW OPENGL_UTILS)