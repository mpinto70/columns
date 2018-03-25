
add_library(
    graphics_mck
    utilgraphics.cpp
)

target_include_directories(
    graphics_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
