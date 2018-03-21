
add_library(
    score
    Score.cpp
    ScoreBoard.cpp
)

target_include_directories(
    score
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
