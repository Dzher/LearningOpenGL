set(PRIVATE_SOURCE
    faceculling.cpp
    faceculling.h
    main.cpp
)

add_executable(facecull ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(facecull GLFW OPENGL_UTILS)