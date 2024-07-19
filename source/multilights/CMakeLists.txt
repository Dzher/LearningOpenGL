set(PRIVATE_SOURCE
    multilights.cpp
    multilights.h
    main.cpp
)

add_executable(multilights ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(multilights GLFW OPENGL_UTILS)