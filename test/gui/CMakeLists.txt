
add_executable(
    testgui
    ../gtest_main.cpp
    ColorTest.cpp
    testeFonte.cpp
    testePonto.cpp
)

target_link_libraries(
    testgui
    gui
    util_mck
    libgtest
    libgmock
)
