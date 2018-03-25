set(game_srcs
    BoardControllerTest.cpp
    MessageTest.cpp
    ControllerTest.cpp
)

set(game_libs
    graphics_mck
    state_mck
    piece_mck
    gui_mck
    util_mck
    game
    graphics
    state
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
