set(PRIVATE_SOURCE
    dopenglwidget.cpp
    dopenglwidget.h
    main.cpp
)

qt5_wrap_cpp(MOC_FILES dopenglwidget.cpp
dopenglwidget.h)

add_executable(hellowidget ${PRIVATE_SOURCE} ${MOC_FILES})
target_link_libraries(hellowidget Qt5::Core Qt5::Gui Qt5::Widgets)