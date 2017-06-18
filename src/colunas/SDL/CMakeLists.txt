
add_library(
    colunas_SDL
    colunas_SDL.cpp
)

target_include_directories(
    colunas_SDL
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
