
add_library(
    columns_SDL
    columns_SDL.cpp
)

target_include_directories(
    columns_SDL
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
