add_library(
    graphics_SDL
    WindowSDL.cpp
    Canvas.cpp
)

target_include_directories(
    graphics_SDL
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
