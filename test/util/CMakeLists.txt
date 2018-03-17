
add_executable(
    testutil
    ../gtest_main.cpp
    RandomTest.cpp
    WaitTest.cpp
)

target_link_libraries(
    testutil
    util
    libgtest
    libgmock
)
