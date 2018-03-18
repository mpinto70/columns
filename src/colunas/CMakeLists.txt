add_subdirectory (SDL)
add_executable (
    colunas
    colunas.cpp
)

include(FindPkgConfig)

find_package(Threads REQUIRED)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
)

target_link_libraries (
    colunas
    colunas_SDL
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    grafico
    grafico_SDL
    gui
    jogo
    piece
    score
    util
)
