add_library(
    game
    Canvas.cpp
    Controller.cpp
    InputReader.cpp
    MatchController.cpp
    PieceController.cpp
    Messages.cpp
)

target_include_directories(
    game
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
