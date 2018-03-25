#pragma once

#include "../mck/graphics/WindowMock.h"

#include "graphics/BoardDrawer.h"
#include "graphics/ScoreBoardDrawer.h"
#include "state/ScoreBoard.h"
#include "state/State.h"

namespace graphics {
namespace mck {

ScoreBoardDrawer create_score_board_drawer();

void prepare_score_board_draw(const ScoreBoardDrawer& drawer,
      ::testing::StrictMock<WindowMock>& window_mock,
      const state::ScoreBoard& score_board);

BoardDrawer create_board_drawer();

void prepare_board_draw(const BoardDrawer& drawer,
      ::testing::StrictMock<WindowMock>& window_mock,
      const state::State& state,
      const gui::Color& elimination_color);
}
}
