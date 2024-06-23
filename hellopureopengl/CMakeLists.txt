set(PRIVATE_SOURCE
    dpureopengl.cpp
    dpureopengl.h
    main.cpp
)

qt5_wrap_cpp(MOC_FILES dpureopengl.cpp
dpureopengl.h)

add_executable(pureopengl ${PRIVATE_SOURCE} ${MOC_FILES})
target_link_libraries(pureopengl Qt5::Core Qt5::Gui Qt5::Widgets)