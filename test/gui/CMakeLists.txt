
add_executable(
    gui_test
    ../gtest_main.cpp
    ColorTest.cpp
    FontTest.cpp
    PointTest.cpp
    RectangleTest.cpp
)

target_link_libraries(
    gui_test
    gui
    util_mck
    gui_mck
    libgtest
    libgmock
)
