
add_library(
    pontuacao
    Score.cpp
    ScoreBoard.cpp
)

target_include_directories(
    pontuacao
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
