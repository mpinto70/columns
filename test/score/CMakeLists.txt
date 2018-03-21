
add_executable(
    testpontuacao
    ../gtest_main.cpp
    ScoreTest.cpp
    ScoreBoardTest.cpp
)

target_link_libraries(
    testpontuacao
    util_mck
    score_mck
    score
    libgtest
    libgmock
)
