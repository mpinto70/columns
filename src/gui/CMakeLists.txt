
add_library(
    gui
    Cor.cpp
    Fonte.cpp
    Ponto.cpp
    Retangulo.cpp
)

target_include_directories(
    gui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
