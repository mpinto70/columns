add_library(
    piece
    Board.cpp
    Piece.cpp
    PieceCreatorRandom.cpp
    PiecePosition.cpp
)

target_include_directories(
    piece
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
