add_library(
    state
    Score.cpp
    ScoreBoard.cpp
    State.cpp
)

target_include_directories(
    state
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
