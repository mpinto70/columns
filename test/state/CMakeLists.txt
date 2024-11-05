set(state_srcs
    ScoreBoardTest.cpp
    ScoreTest.cpp
    StateTest.cpp
)

set(state_libs
    state_mck
    piece_mck
    gui_mck
    util_mck
    piece
    gui
    state
    util
)

add_unit_test(
    state
    state_srcs
    state_libs
)
