
add_executable(
    testutil
    ../gtest_main.cpp
    RandomTest.cpp
    testeEspera.cpp
)

target_link_libraries(
    testutil
    util
    libgtest
    libgmock
)
