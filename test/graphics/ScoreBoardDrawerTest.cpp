#include "../mck/graphics/WindowMock.h"

#include "../mck/graphics/utilgraphics.h"

#include "graphics/ScoreBoardDrawer.h"

#include <gtest/gtest.h>

namespace graphics {
namespace tst {
using ::testing::StrictMock;

TEST(ScoreBoardDrawerTest, draw) {
    StrictMock<mck::WindowMock> window_mock("name", 125, 500);
    const auto drawer = mck::create_score_board_drawer();
    const state::ScoreBoard score_board{ state::Score{ 200 }, state::Score{ 37 } };
    const state::State state(piece::Board(8, 16, gui::Color::WHITE), score_board);
    mck::prepare_score_board_draw(window_mock, score_board);
    drawer->draw(window_mock, state);
}
}
}
