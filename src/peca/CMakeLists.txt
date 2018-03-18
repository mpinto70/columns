
add_library(
    peca
    Board.cpp
    Piece.cpp
    PiecePosition.cpp
)

target_include_directories(
    peca
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
