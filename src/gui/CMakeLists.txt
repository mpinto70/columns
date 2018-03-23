
add_library(
    gui
    Font.cpp
)

target_include_directories(
    gui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
