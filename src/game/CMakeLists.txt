add_library(
    game
    BoardController.cpp
    Canvas.cpp
    Controller.cpp
    GameControllerOld.cpp
    InputReader.cpp
    MatchController.cpp
    PieceController.cpp
    Messages.cpp
)

target_include_directories(
    game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
