
add_executable(
    piece_test
    ../gtest_main.cpp
    BoardTest.cpp
    PieceTest.cpp
    PiecePositionTest.cpp
)

target_link_libraries(
    piece_test
    util_mck
    piece_mck
    gui_mck
    libgtest
    libgmock
    piece
    gui
    util
)
