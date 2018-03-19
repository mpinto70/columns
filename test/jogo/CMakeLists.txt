
add_executable(
    testjogo
    ../gtest_main.cpp
    BoardControllerTest.cpp
    MessageTest.cpp
    StateTest.cpp
)

target_link_libraries(
    testjogo
    peca_mck
    gui_mck
    libgtest
    libgmock
    jogo
    score
    piece
    gui
    util
)
