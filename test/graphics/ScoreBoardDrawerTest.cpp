#include "ScoreBoardDrawerTest.h"

#include "../mck/graphics/utilgraphics.h"

#include "graphics/ScoreBoardDrawer.h"

namespace graphics {
namespace tst {

void ScoreBoardDrawerTest::SetUp() {
    window_mock.reset(new StrictMock<mck::WindowMock>("name", 125, 500));
}

void ScoreBoardDrawerTest::TearDown() {
    window_mock.reset();
}

TEST_F(ScoreBoardDrawerTest, draw) {
    const ScoreBoardDrawer drawer = mck::create_score_board_drawer();
    const state::ScoreBoard score_board{ state::Score{ 200 }, state::Score{ 37 } };
    mck::prepare_score_board_draw(drawer, *window_mock, score_board);
    drawer.draw(window_mock, score_board);
}
}
}
