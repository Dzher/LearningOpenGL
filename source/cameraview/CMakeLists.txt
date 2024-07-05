set(PRIVATE_SOURCE
    cameraview.cpp
    cameraview.h
    main.cpp
)

add_executable(cameraview ${PRIVATE_SOURCE} ${GLAD_SRC})
target_link_libraries(cameraview GLFW OPENGL_UTILS)