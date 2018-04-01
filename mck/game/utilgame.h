#pragma once

#include "../mck/game/CanvasMock.h"

namespace game {
namespace mck {

void prepare_state_draw(::testing::StrictMock<CanvasMock>& canvas_mock,
      const state::State& state);
}
}
