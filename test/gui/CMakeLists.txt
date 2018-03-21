
add_executable(
    testgui
    ../gtest_main.cpp
    ColorTest.cpp
    FontTest.cpp
    PointTest.cpp
    RectangleTest.cpp
)

target_link_libraries(
    testgui
    gui
    util_mck
    gui_mck
    libgtest
    libgmock
)
