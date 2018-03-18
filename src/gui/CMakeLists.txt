
add_library(
    gui
    Color.cpp
    Fonte.cpp
    Retangulo.cpp
)

target_include_directories(
    gui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
