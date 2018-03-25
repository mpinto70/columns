set(graphics_srcs
    ScoreBoardDrawerTest.cpp
    BoardDrawerTest.cpp
)

set(graphics_libs
    state_mck
    piece_mck
    graphics_mck
    gui_mck
    graphics
    state
    piece
    gui
    util
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    graphics
    graphics_srcs
    graphics_libs
)
