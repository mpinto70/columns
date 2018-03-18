
add_executable(
    testjogo
    ../gtest_main.cpp
    #testeControladorTabuleiro.cpp
    testeSituacao.cpp
)

target_link_libraries(
    testjogo
    peca_mck
    gui_mck
    libgtest
    libgmock
    jogo
    pontuacao
    piece
    gui
    util
)
