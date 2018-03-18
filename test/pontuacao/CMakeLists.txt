
add_executable(
    testpontuacao
    ../gtest_main.cpp
    testePlacar.cpp
    ScoreTest.cpp
)

target_link_libraries(
    testpontuacao
    util_mck
    pontuacao
    libgtest
    libgmock
)
