
add_library(
    score_mck
    utilscore.cpp
)

target_include_directories(
    score_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
