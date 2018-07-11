add_library(
    piece_mck
    utilpiece.cpp
    CreatorCycle.cpp
)

target_include_directories(
    piece_mck
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
