
add_executable (
    colunas
    colunas.cpp
)

find_package(Threads REQUIRED)

target_link_libraries (
    colunas
    grafico
    grafico_SDL
    gui
    jogo
    peca
    pontuacao
    util
    ${CMAKE_THREAD_LIBS_INIT}
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
)
