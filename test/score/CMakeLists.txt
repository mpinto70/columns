set(score_srcs
    ScoreTest.cpp
    ScoreBoardTest.cpp
)

set(score_libs
    util_mck
    score_mck
    score
    libgtest
    libgmock
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

add_unit_test(
    score
    score_srcs
    score_libs
)
