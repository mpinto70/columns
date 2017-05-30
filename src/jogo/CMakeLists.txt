
add_library(
    jogo
    ControladorJogo.cpp
    ControladorTabuleiro.cpp
    Mensagem.cpp
    Situacao.cpp
)

target_include_directories(
    jogo
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
