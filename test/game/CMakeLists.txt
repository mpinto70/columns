set(game_srcs
    CanvasTest.cpp
    ControllerTest.cpp
    InputReaderTest.cpp
    MatchControllerTest.cpp
    PieceControllerTest.cpp
    MessagesTest.cpp
)

set(game_libs
    game_mck
    state_mck
    piece_mck
    gui_mck
    util_mck
    game
    state
    piece
    gui
    util
)

add_unit_test(
    game
    game_srcs
    game_libs
)
