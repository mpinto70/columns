set(gui_srcs
    ColorTest.cpp
    FontTest.cpp
)

set(gui_libs
    gui
    util_mck
    gui_mck
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    gui
    gui_srcs
    gui_libs
)
