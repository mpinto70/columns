
add_library(
    peca_mck
    utilpeca.cpp
)

target_include_directories(
    peca_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
