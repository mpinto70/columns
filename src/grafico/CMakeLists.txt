
add_subdirectory (SDL)

add_library(
    grafico
    DesenhaTabuleiro.cpp
    Janela.cpp
)

target_include_directories(
    grafico
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
