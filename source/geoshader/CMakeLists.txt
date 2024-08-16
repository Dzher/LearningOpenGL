set(PRIVATE_SOURCE
    geoshader.cpp
    geoshader.h
    main.cpp
)

add_executable(geoshader ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(geoshader GLFW OPENGL_UTILS)