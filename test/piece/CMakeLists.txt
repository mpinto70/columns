set(piece_srcs
    BoardTest.cpp
    CreatorRandomTest.cpp
    PositionTest.cpp
    PieceTest.cpp
)

set(piece_libs
    piece
    util_mck
    piece_mck
    gui_mck
    piece
    gui
    util
)

add_unit_test(
    piece
    piece_srcs
    piece_libs
)
