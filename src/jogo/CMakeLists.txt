
add_library(
    jogo
    ControladorJogo.cpp
    BoardController.cpp
    Mensagem.cpp
    State.cpp
)

target_include_directories(
    jogo
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
