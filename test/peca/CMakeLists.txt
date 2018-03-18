
add_executable(
    testpeca
    ../gtest_main.cpp
    BoardTest.cpp
    PieceTest.cpp
    PiecePositionTest.cpp
)

target_link_libraries(
    testpeca
    util_mck
    peca_mck
    gui_mck
    libgtest
    libgmock
    peca
    gui
    util
)
