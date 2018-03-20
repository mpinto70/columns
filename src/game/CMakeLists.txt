
add_library(
    game
    GameController.cpp
    BoardController.cpp
    Message.cpp
    State.cpp
)

target_include_directories(
    game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
