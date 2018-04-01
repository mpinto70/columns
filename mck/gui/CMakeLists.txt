add_library(
    gui_mck
    utilgui.cpp
)

target_include_directories(
    gui_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
