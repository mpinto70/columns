
add_library(
    game_mck
    utilgame.cpp
)

target_include_directories(
    game_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
