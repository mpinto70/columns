set(graphics_srcs
    ScoreBoardDrawerTest.cpp
)

set(graphics_libs
    score_mck
    piece_mck
    gui_mck
    graphics
    score
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
