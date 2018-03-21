
add_executable(
    testjogo
    ../gtest_main.cpp
    BoardControllerTest.cpp
    MessageTest.cpp
    StateTest.cpp
)

target_link_libraries(
    testjogo
    game_mck
    score_mck
    peca_mck
    gui_mck
    libgtest
    libgmock
    game
    score
    piece
    gui
    util
)
