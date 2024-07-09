set(PRIVATE_SOURCE
    phonglighting.cpp
    phonglighting.h
    main.cpp
)

add_executable(phonglighting ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(phonglighting GLFW OPENGL_UTILS)