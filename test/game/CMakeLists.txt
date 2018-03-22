set(game_srcs
    BoardControllerTest.cpp
    MessageTest.cpp
    StateTest.cpp
)

set(game_libs
    game_mck
    score_mck
    piece_mck
    gui_mck
    game
    score
    piece
    gui
    util
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    game
    game_srcs
    game_libs
)
