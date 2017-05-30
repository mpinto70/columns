
add_library(
    util
    Aleatorio.cpp
    Espera.cpp
)

target_include_directories(
    util
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
