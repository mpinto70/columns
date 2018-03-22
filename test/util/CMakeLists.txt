
add_executable(
    util_test
    ../gtest_main.cpp
    RandomTest.cpp
    WaitTest.cpp
)

target_link_libraries(
    util_test
    util
    libgtest
    libgmock
)
