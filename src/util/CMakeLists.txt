add_library(
    util
    Random.cpp
    Wait.cpp
)

target_include_directories(
    util
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
