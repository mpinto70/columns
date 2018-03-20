
add_library(
    jogo
    GameController.cpp
    BoardController.cpp
    Message.cpp
    State.cpp
)

target_include_directories(
    jogo
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
