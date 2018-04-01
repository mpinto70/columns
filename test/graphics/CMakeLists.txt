set(graphics_srcs
    BoardDrawerTest.cpp
    ScoreBoardDrawerTest.cpp
    WindowTest.cpp
)

set(graphics_libs
    state_mck
    graphics_mck
    piece_mck
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
