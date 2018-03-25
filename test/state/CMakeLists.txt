set(state_srcs
    ScoreTest.cpp
    ScoreBoardTest.cpp
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
    libgtest
    libgmock
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    state
    state_srcs
    state_libs
)
