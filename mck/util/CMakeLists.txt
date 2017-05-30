
add_library(
    util_mck
    utiltst.cpp
)

target_include_directories(
    util_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
