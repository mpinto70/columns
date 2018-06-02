add_library(
    input_SDL
    InputReader.cpp
)

target_include_directories(
    input_SDL
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
