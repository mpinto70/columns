add_library(
    piece
    Board.cpp
    CreatorRandom.cpp
    Piece.cpp
    Position.cpp
)

target_include_directories(
    piece
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
