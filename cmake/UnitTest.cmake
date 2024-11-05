include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

function(add_unit_test test_name sources_var libs_var)
    set(unit_test_name unit_${test_name})

    add_executable(
        ${unit_test_name}
        ${${sources_var}}
    )

    target_link_libraries(
        ${unit_test_name}
        ${${libs_var}}
        GTest::gtest_main
        GTest::gmock
    )

    include(GoogleTest)
    gtest_discover_tests(${unit_test_name})
endfunction(add_unit_test)

function(add_mock_lib mock_lib_name sources_var)
    add_library(
        ${mock_lib_name}
        ${${sources_var}}
    )

    target_link_libraries(
        ${mock_lib_name}
        GTest::gtest_main
        GTest::gmock
    )
endfunction(add_mock_lib)
