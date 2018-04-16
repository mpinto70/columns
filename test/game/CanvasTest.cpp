#include "../mck/game/CanvasMock.h"
#include "../mck/piece/utilpiece.h"
#include "../mck/state/utilstate.h"

#include "game/Canvas.h"

#include <gtest/gtest.h>

namespace game {
namespace tst {
using ::testing::StrictMock;

TEST(CanvasTest, draw_state) {
    StrictMock<mck::CanvasMock> canvas_mock;
    piece::SharedConstBoard board = std::make_shared<piece::Board>(8, 16);
    const auto state = state::mck::create_state(board);
    EXPECT_CALL(canvas_mock, clear()).Times(1);
    EXPECT_CALL(canvas_mock, draw_(state->board())).Times(1);
    EXPECT_CALL(canvas_mock, draw_(state->score_board())).Times(1);

    canvas_mock.draw(*state);
}

TEST(CanvasTest, draw_state_with_falling_piece) {
    StrictMock<mck::CanvasMock> canvas_mock;
    piece::SharedConstBoard board = std::make_shared<piece::Board>(8, 16);
    state::StatePtr state = std::make_unique<state::StateFalling>(board,
          state::ScoreBoard{ state::Score{ 150 }, state::Score{ 20 } },
          piece::Piece{ { gui::Color::LAVENDER, gui::Color::RED, gui::Color::RED } },
          piece::Piece{ { gui::Color::RED, gui::Color::BLUE, gui::Color::GREEN } },
          piece::PiecePosition(*board, 4, 2));
    EXPECT_CALL(canvas_mock, clear()).Times(1);
    EXPECT_CALL(canvas_mock, draw_(state->board())).Times(1);
    EXPECT_CALL(canvas_mock, draw_(state->score_board())).Times(1);
    EXPECT_CALL(canvas_mock, draw_(state->piece(), state->piece_position())).Times(1);
    EXPECT_CALL(canvas_mock, draw_next_(state->next())).Times(1);

    canvas_mock.draw(*state);
}
}
}
