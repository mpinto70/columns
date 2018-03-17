
add_library(
    util
    Random.cpp
    Espera.cpp
)

target_include_directories(
    util
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
