set(piece_srcs
    BoardTest.cpp
    PiecePositionTest.cpp
    PieceTest.cpp
)

set(piece_libs
    piece
    util_mck
    piece_mck
    gui_mck
    libgtest
    libgmock
    piece
    gui
    util
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    piece
    piece_srcs
    piece_libs
)
