
add_library(
    pontuacao
    Placar.cpp
    Pontuacao.cpp
)

target_include_directories(
    pontuacao
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
