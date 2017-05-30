
add_executable(
    testpontuacao
    ../gtest_main.cpp
    testePlacar.cpp
    testePontuacao.cpp
)

target_link_libraries(
    testpontuacao
    pontuacao
    libgtest
    libgmock
)
