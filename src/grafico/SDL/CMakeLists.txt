
add_library(
    grafico_SDL
    JanelaSDL.cpp
)

target_include_directories(
    grafico_SDL
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
