
add_library(
    peca
    Piece.cpp
    PosicaoPeca.cpp
    Tabuleiro.cpp
)

target_include_directories(
    peca
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
