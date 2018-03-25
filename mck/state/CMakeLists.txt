
add_library(
    state_mck
    utilstate.cpp
)

target_include_directories(
    state_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
