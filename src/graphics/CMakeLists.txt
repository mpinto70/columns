
add_subdirectory (SDL)

add_library(
    graphics
    BoardDrawer.cpp
    Window.cpp
)

target_include_directories(
    graphics
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
