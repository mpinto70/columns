set(util_srcs
    RandomTest.cpp
    WaitTest.cpp
)

set(util_libs
    util
)

add_unit_test(
    util
    util_srcs
    util_libs
)
