
add_library(
    gui
    Color.cpp
    Font.cpp
)

target_include_directories(
    gui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
