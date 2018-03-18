
add_executable(
    testgui
    ../gtest_main.cpp
    ColorTest.cpp
    testeFonte.cpp
    PointTest.cpp
)

target_link_libraries(
    testgui
    gui
    util_mck
    libgtest
    libgmock
)
