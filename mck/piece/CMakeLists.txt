
add_library(
    peca_mck
    utilpiece.cpp
)

target_include_directories(
    peca_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
