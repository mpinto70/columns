
add_executable(
    score_test
    ../gtest_main.cpp
    ScoreTest.cpp
    ScoreBoardTest.cpp
)

target_link_libraries(
    score_test
    util_mck
    score_mck
    score
    libgtest
    libgmock
)
