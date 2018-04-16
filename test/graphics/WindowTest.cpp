#include "../mck/graphics/WindowMock.h"
#include "../mck/piece/utilpiece.h"
#include "../mck/state/utilstate.h"

#include "graphics/Window.h"

#include <gtest/gtest.h>

namespace graphics {
namespace tst {
using ::testing::StrictMock;

TEST(WindowTest, draw_state) {
    StrictMock<mck::WindowMock> window_mock("name", 125, 500);
    piece::SharedConstBoard board = std::make_shared<piece::Board>(8, 16);
    const auto state = state::mck::create_state(board);
    EXPECT_CALL(window_mock, clear()).Times(1);
    EXPECT_CALL(window_mock, draw_(state->board())).Times(1);
    EXPECT_CALL(window_mock, draw_(state->score_board())).Times(1);

    window_mock.draw(*state);
}

TEST(WindowTest, draw_state_with_falling_piece) {
    StrictMock<mck::WindowMock> window_mock("name", 125, 500);
    const piece::SharedConstBoard board = std::make_shared<piece::Board>(8, 16);
    state::StatePtr state = std::make_unique<state::StateFalling>(board,
          state::ScoreBoard{ state::Score{ 150 }, state::Score{ 20 } },
          piece::Piece{ { gui::Color::LAVENDER, gui::Color::RED, gui::Color::RED } },
          piece::Piece{ { gui::Color::RED, gui::Color::BLUE, gui::Color::GREEN } },
          piece::PiecePosition(*board, 4, 2));
    EXPECT_CALL(window_mock, clear()).Times(1);
    EXPECT_CALL(window_mock, draw_(state->board())).Times(1);
    EXPECT_CALL(window_mock, draw_(state->score_board())).Times(1);
    EXPECT_CALL(window_mock, draw_(state->piece(), state->piece_position())).Times(1);
    EXPECT_CALL(window_mock, draw_next_(state->next())).Times(1);

    window_mock.draw(*state);
}
}
}
