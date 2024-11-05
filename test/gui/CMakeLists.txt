set(gui_srcs
    ColorTest.cpp
    FontTest.cpp
)

set(gui_libs
    gui
    util_mck
    gui_mck
)

add_unit_test(
    gui
    gui_srcs
    gui_libs
)
