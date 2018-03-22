
add_executable(
    game_test
    ../gtest_main.cpp
    BoardControllerTest.cpp
    MessageTest.cpp
    StateTest.cpp
)

target_link_libraries(
    game_test
    game_mck
    score_mck
    piece_mck
    gui_mck
    libgtest
    libgmock
    game
    score
    piece
    gui
    util
)
