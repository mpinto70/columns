add_library(
    game
    BoardController.cpp
    Canvas.cpp
    Controller.cpp
    GameController.cpp
    InputReader.cpp
    PieceController.cpp
    Messages.cpp
)

target_include_directories(
    game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
